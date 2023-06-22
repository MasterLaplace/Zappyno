"""
Client class is used to store information about the client, such as
the host, the port, the IA, the team name, the communication object…
"""

from selectors import EVENT_READ, EVENT_WRITE
from sys import exit as sys_exit
from enum import Enum
from subprocess import Popen
from communication import Communication
from player import Player

class State(Enum):
    """
    The class is used to store information about the step of the game.
    """
    UNINITIALIZED = 0
    SENT_TEAM = 1
    SAVED_ID = 2
    SAVED_INFOS = 3

class Client:
    """
    The class is used to store information about the client.
    """
    def __init__(self, host: str, port: int, team: str):
        self.__host = host
        self.__port = port
        self.__team = team
        self.__id: int = 0
        self.__state: State = State.UNINITIALIZED
        self.__communication = Communication(host, port)
        self.__player = Player()
        self.__is_logged: bool = False
        self.__message: str = ''

    def loop(self) -> None:
        """
        The main loop of the client.
        """
        self.__communication.connect()
        while True:
            for _, mask in self.__communication.select():
                if mask & EVENT_READ:
                    self.__handle_read()
                elif mask & EVENT_WRITE:
                    self.__handle_write()

    def __handle_read(self) -> None:
        """
        Handle read selector from select.
        """
        received: str = self.__communication.receive()

        if received:
            self.__message += received
        else:
            self.__communication.disconnect()
        splitted: list = self.__message.split('\n')
        for line in splitted[:-1]:
            self.__handle_line(line)

    def __handle_write(self) -> None:
        """
        Handle write selector from select.
        """
        if not self.__player.is_running:
            return
        if self.__is_logged:
            self.__player.logical()
        if self.__player.response:
            if not self.__is_logged and self.__player.response == self.__team:
                self.__state = State.SENT_TEAM
            # print(f'\tSending: {self.__id} -> {self.__player.response}')
            self.__communication.send(self.__player.response)
            self.__player.is_running = False

    def __handle_line(self, line: str) -> None:
        """
        Handle line received from the server.
        """
        if 'dead' in line:
            self.__handle_death()
        elif 'WELCOME' in line and self.__state == State.UNINITIALIZED:
            self.__handle_welcome()
        elif self.__state != State.SAVED_INFOS:
            self.__store_infos(line)
        elif 'Elevation underway' in line:
            self.__player.step = 8
        elif 'Current level:' in line:
            print(f'Current level: {line}')
        elif self.__state == State.SAVED_INFOS and 'message' in line:
            if self.__player.delete_read:
                self.__player.delete_read = False
                self.__message = self.__message.split('\n')[-1]
                return
            self.__player.parse_broadcast(line)
            self.__message = self.__message.split('\n')[-1]
            return
        elif 'ok' in line and 'Take' in self.__player.response and 'food' not in self.__player.response:
            self.__player.refresh_shared_inventory()
            self.__player.new_object = True
        elif 'Inventory' in self.__player.response:
            self.__player.parse_inventory(line)
        elif 'Look' in self.__player.response:
            self.__player.fov = line
        elif 'Connect_nbr' in self.__player.response:
            self.__player.unused_slots = int(line)
            if self.__player.unused_slots > 0 and self.__player.fork:
                Popen(['python3', 'zappy_ai', '-p', str(self.__port), '-n', self.__team, '-h', self.__host])
                self.__player.fork = False
                print('A new IA has been forked')
        self.__message = self.__message.split('\n')[-1]
        self.__player.is_running = True

    def __handle_death(self) -> None:
        """
        Handle death of the IA. It disconnects the client and exit the program.
        """
        print(f'IA n°{self.__id} is dead.')
        self.__communication.disconnect()
        sys_exit(0)

    def __handle_welcome(self) -> None:
        """
        Handle welcome message from the server.
        """
        self.__player.response = self.__team

    def __store_infos(self, line: str) -> None:
        """
        Store the width and the height of the map received from the server.
        """
        if 'message' in line:
            return
        if self.__state == State.SENT_TEAM:
            self.__id = int(line)
            self.__player.player_id = self.__id
            self.__player.available_slots = self.__id
            self.__player.response = ''
            self.__state = State.SAVED_ID
            return
        self.__player.response = ''
        self.__player.is_running = True
        self.__state = State.SAVED_INFOS
        self.__is_logged = True
        print('Logged in!', self.__id)

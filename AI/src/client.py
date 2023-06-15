"""
Client class is used to store information about the client, such as
the host, the port, the IA, the team name, the communication object…
"""

from selectors import EVENT_READ, EVENT_WRITE
from sys import exit as sys_exit
from enum import Enum
from communication import Communication
from player import Player

class State(Enum):
    """
    The class is used to store information about the step of the game.
    """
    UNINITIALIZED = 0
    SENT_TEAM = 1
    SAVED_SLOT = 2
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
        self.__player = Player(self.__communication, self.__team, self.__id)
        self.__is_logged: bool = False
        self.__width: int = 0
        self.__height: int = 0

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

    def useless(self) -> None:
        """
        This temporary method is used to avoid the linter error.
        """
        print(self.__host)
        print(self.__port)
        print(self.__team)
        print(self.__communication)
        print(self.__player)
        print(self.__is_logged)
        print(self.__width)
        print(self.__height)

    def __handle_read(self) -> None:
        """
        Handle read selector from select.
        """
        message: str = ''
        received: str = self.__communication.receive()

        if received:
            message += received
        else:
            self.__communication.disconnect()
        splitted: list = message.split('\n')
        for line in splitted[:-1]:
            self.__handle_line(line)

    def __handle_write(self) -> None:
        """
        Handle write selector from select.
        """
        if not self.__player.is_running:
            return
        if self.__is_logged:
            print('Run/Play client')
        if self.__player.response:
            if not self.__is_logged and self.__player.response[:-1] == self.__team:
                self.__state = State.SENT_TEAM
            self.__communication.send(self.__player.response)
            self.__player.is_running = False

    def __handle_line(self, line: str) -> None:
        """
        Handle line received from the server.
        """
        if 'dead' in line:
            self.__handle_death()
        elif 'WELCOME' in line and not self.__is_logged:
            self.__handle_welcome()
        elif self.__state != State.SAVED_INFOS:
            self.__store_infos(line)
        else:
            print('Received: ' + line)

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
        self.__player.response = self.__team + '\n'

    def __store_infos(self, line: str) -> None:
        """
        Store the width and the height of the map received from the server.
        """
        splitted = line.split()

        if 'message' in line:
            return
        if self.__state == State.SENT_TEAM:
            # self.__player.empty_slot = int(line)
            self.__player.response = ''
            self.__state = State.SAVED_SLOT
            return
        self.__width = int(splitted[0])
        self.__height = int(splitted[1])
        self.__player.response = ''
        self.__player.is_running = True
        self.__state = State.SAVED_INFOS
        self.__is_logged = True

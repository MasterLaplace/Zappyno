"""
Client class is used to store information about the client, such as
the host, the port, the IA, the team name, the communication object…
"""

from selectors import EVENT_READ, EVENT_WRITE
from sys import exit as sys_exit
from communication import Communication
from player import Player

class Client:
    """
    The class is used to store information about the client.
    """
    def __init__(self, host: str, port: int, team: str):
        self.__host = host
        self.__port = port
        self.__team = team
        self.__id: int = 0
        self.__communication = Communication(host, port)
        self.__player = Player(self.__communication, self.__team, self.__id)
        self.__has_logged: bool = False

    def loop(self) -> None:
        """
        The main loop of the client.
        """
        # message: str = ''
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

    def __handle_read(self) -> None:
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
        pass

    def __handle_line(self, line: str) -> None:
        if "dead" in line:
            self.__handle_death()
        elif "WELCOME" in line and not self.__has_logged:
            self.__handle_welcome()
        else:
            print('Received: ' + line)

    def __handle_death(self) -> None:
        print(f'IA n°{self.__id} is dead.')
        self.__communication.disconnect()
        sys_exit(0)

    def __handle_welcome(self) -> None:
        self.__player.response = self.__team + '\n'

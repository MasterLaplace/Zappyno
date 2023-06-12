"""
Client class is used to store information about the client, such as
the host, the port, the IA, the team name, the communication object…
"""

from selectors import EVENT_READ, EVENT_WRITE
from communication import Communication

class Client:
    """
    The class is used to store information about the client.
    """
    def __init__(self, host: str, port: int, team: str):
        self.__host = host
        self.__port = port
        self.__team = team
        self.__communication = Communication(host, port)
        self.__player = None

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
        pass

    def __handle_write(self) -> None:
        pass

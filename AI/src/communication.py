"""This module is used to communicate with the server."""
from socket import socket, AF_INET, SOCK_STREAM
from selectors import DefaultSelector, EVENT_READ, EVENT_WRITE

class Communication:
    """
    This class is used to communicate with the server.
    It is used to connect to the server, send data to the server, and receive data from the server.
    """
    def __init__(self, host: str, port: int):
        self.__host = host
        self.__port = port
        self.__socket = socket(AF_INET, SOCK_STREAM)
        self.__selector = DefaultSelector()
        self.__socket.setblocking(False)

    def __str__(self) -> str:
        return self.__host + ':' + str(self.__port)

    def get_host(self) -> str:
        """Get the host of the server."""
        return self.__host

    def get_port(self) -> int:
        """Get the port of the server."""
        return self.__port

    def connect(self) -> None:
        """Connect to the server using the host and port previously provided."""
        self.__socket.connect((self.__host, self.__port))
        self.__selector.register(self.__socket, EVENT_READ | EVENT_WRITE)

    def disconnect(self) -> None:
        """Disconnect from the server."""
        self.__selector.unregister(self.__socket)
        self.__socket.close()

    def send(self, data: str) -> None:
        """Send data to the server with adding a newline character at the end"""
        message: str = data + '\n'

        self.__socket.send(message.encode())

    def receive(self) -> str:
        """
        Receive data from the server.
        The maximum amount of data that can be received is 1024 bytes.
        """
        return self.__socket.recv(1024).decode()

    def select(self):
        """
        Select the socket.
        This method is used to check if the socket is ready to be read or written.
        """
        return self.__selector.select(timeout=None)

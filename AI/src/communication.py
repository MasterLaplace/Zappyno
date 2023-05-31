"""This module is used to communicate with the server."""
from socket import socket, AF_INET, SOCK_STREAM

class Communication:
    """
    This class is used to communicate with the server.
    It is used to connect to the server, send data to the server, and receive data from the server.
    """
    def __init__(self, host: str, port: int):
        self.__host = host
        self.__port = port
        self.__socket = socket(AF_INET, SOCK_STREAM)

    def __str__(self) -> str:
        return self.__host + ':' + str(self.__port)

    def get_host(self):
        """Get the host of the server."""
        return self.__host

    def get_port(self):
        """Get the port of the server."""
        return self.__port

    def connect(self):
        """Connect to the server using the host and port previously provided."""
        self.__socket.connect((self.__host, self.__port))

    def disconnect(self):
        """Disconnect from the server."""
        self.__socket.close()

    def send(self, data: str):
        """Send data to the server with adding a newline character at the end"""
        message: str = data + '\n'

        self.__socket.send(message.encode())

    def receive(self):
        """
        Receive data from the server.
        The maximum amount of data that can be received is 1024 bytes.
        """
        return self.__socket.recv(1024).decode()

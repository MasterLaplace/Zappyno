"""
Player class is used to store information about the player.
"""

from communication import Communication

class Player:
    """
    This class is used to store information about the player.
    It is used to store the team name, the communication object, the level of the player.
    """
    def __init__(self, communication: Communication, team: str, position: str):
        self.__team = team
        self.__communication = communication
        self.__level = 1
        self.__inventory = {
            'food': 0,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }
        self.__position = position

    def get_team(self) -> str:
        """
        Get the team name of the player.
        """
        return self.__team

    def get_communication(self) -> Communication:
        """
        Get the communication object of the player.
        """
        return self.__communication

    def send_message(self) -> None:
        """
        Send a message to the server.
        """
        self.__communication.send('test')

    def receive_message(self) -> None:
        """
        Receive a message from the server.
        """
        self.__communication.receive()

    def get_level(self) -> int:
        """
        Get the level of the player.
        """
        return self.__level

    def set_level(self):
        """
        Set the level of the player.
        """
        self.__level += 1

    def get_inventory(self) -> dict:
        """
        Get the inventory of the player.
        """
        return self.__inventory

    def add_inventory(self, object: str) -> None:
        """
        Add an item to the inventory of the player.
        """
        self.__inventory[object] += 1


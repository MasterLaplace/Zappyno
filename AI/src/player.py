"""
Player class is used to store information about the player.
"""

from communication import Communication
class Player:
    """
    This class is used to store information about the player.
    It is used to store the team name, the communication object, the level of the player.
    """
    def __init__(self, communication: Communication, team: str, position: str, number: int):
        self.__id = number
        self.__team = team
        self.__communication = communication
        self.__level = 1
        self.__inventory = ""
        self.__position = position
        self.__object = [""]

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

    def send_message(self, message: str) -> None:
        """
        Send a message to the server.
        """
        self.__communication.send(message)

    def receive_message(self) -> str:
        """
        Receive a message from the server.
        """
        return self.__communication.receive()

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

    def get_inventory(self) -> str:
        """
        Get the inventory of the player.
        """
        return self.__inventory

    def add_inventory(self) -> None:
        """
        Add an item to the inventory of the player.
        """
        self.send_message("Inventory")
        self.__inventory = self.receive_message()

    def get_position(self) -> str:
        """
        Get the position of the player.
        """
        return self.__position

    def set_position(self, position: str) -> None:
        """
        Set the position of the player.
        """
        self.__position = position

    def get_id(self) -> int:
        """
        Get the id of the player.
        """
        return self.__id

    def look(self) -> None:
        """
        Look around the player.
        """
        self.send_message("Look")
        self.__object = self.receive_message().split(',')

    def take_object(self) -> None:
        """
        Take an object.
        """
        first_slot = self.__object[0].split(' ')
        self.send_message("Take " + first_slot[2])
        self.receive_message()
        self.look()

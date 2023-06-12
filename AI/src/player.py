"""
Player class is used to store information about the player.
"""

from typing import Dict, List
from communication import Communication

lvls: List[Dict[str, int]] = [
        {"linemate": 1},
        {"linemate": 1, "deraumere": 1, "sibur": 1},
        {"linemate": 2, "sibur": 1, "phiras": 2},
        {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
]

class Player:
    """
    This class is used to store information about the player.
    It is used to store the team name, the communication object, the level of the player.
    """
    def __init__(self, communication: Communication, team: str, number: int):
        self._id = number
        self._team = team
        self.__communication = communication
        #self.__level = 1
        self.__inventory = ""
        self.__object: Dict[int, str] = {}
        #self.__incantation: bool = False
        self.__shared_inventory: Dict[str, int] = {}
        #self.__player_ready_to_incantation: bool = False
        #self.__players_in_incantation: int = 0

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

    def add_inventory(self) -> None:
        """
        Add an item to the inventory of the player.
        """
        self.send_message("Inventory")
        self.__inventory = self.receive_message()
        print(self.__inventory)

    def look(self) -> None:
        """
        Look around the player.
        """
        self.send_message("Look")
        object_string: str = self.receive_message()
        characters_to_remove = "[]\n"
        modified_string = "".join(char for char in
        object_string if char not in characters_to_remove)
        object_list: list = modified_string.split(',')
        for i, item in enumerate(object_list):
            self.__object[i+1] = item

    def take_object(self) -> None:
        """
        Take an object.
        """
        object_take: str = self.__object[1].split(' ')[2]
        self.send_message("Take " + object_take)
        self.receive_message()
        self.look()

    def fill_shared_inventory(self, message: str) -> None:
        """
        Fill the shared inventory.
        """
        object_take: str = message.split(' ')[1]
        if object_take in self.__shared_inventory:
            self.__shared_inventory[object_take] += 1
        else:
            self.__shared_inventory[object_take] = 1

    def parse_brodcast(self, message: str) -> None:
        """
        Parse the broadcast message.
        :param message:
        """
        if message == "Inventory":
            return self.send_message("Inventory")
        if message == "Incantation":
            return self.send_message("Incantation")
        if message == "Ready":
            return self.send_message("Ready")
        if message == "Moving":
            return self.send_message("Moving")
        return None

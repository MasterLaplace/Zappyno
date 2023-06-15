"""
Player class is used to store information about the player.
"""
import math
from typing import Dict, List
from enum import Enum
import random
import re
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

class Movement(Enum):
    """
    This class is used to store the different movement of the player.
    """
    FORWARD = "Forward"
    LEFT = "Left"
    RIGHT = "Right"

class Command(Enum):
    """
    This class is used to store the different command of the player.
    """
    INVENTORY = "Inventory"
    LOOK = "Look"
    TAKE = "Take "

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
        self.__map: List[List[int]] = [[]]
        self.is_running: bool = True
        self.response: str = ''
        self.fork: bool = True

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
        self.create_map(object_string)
        print(self.__object)

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

    def create_map(self, look: str) -> None:
        """
        Create a map of the look.
        :param look:
        """
        row_increment = 1
        vertical_offset = 8
        horizontal_offset = 0

        data: list = []
        separated_look: list = look.split(',')
        look_length: int = len(separated_look)
        for i in range(look_length):
            data.append(' '.join(re.split(r'\'\W+', separated_look[i])[1:]))
        length: int = len(data)
        nb_line: int = int(math.sqrt(length))
        for i in range(nb_line):
            target_row = vertical_offset - horizontal_offset
            column = 0
            while column < row_increment:
                self.__map[target_row][horizontal_offset] += data[i]
                target_row += 1
                i += 1
                column += 1
            row_increment += 2
            horizontal_offset += 1

    def array_size(self, array: list) -> int:
        """
        Get the size of the array.
        :param array:
        """
        number = 0
        for elem in array:
            if not bool(elem):
                return number
            number += 1
        return number

    def search_object(self, obj: str) -> List:
        """
        Search an object in the map.
        :param self:
        :param obj:
        """
        vertical_offset = 8
        horizontal_offset = 0

        while horizontal_offset < self.array_size(self.__map[vertical_offset]):
            if obj == self.__map[vertical_offset][horizontal_offset]:
                return [vertical_offset, horizontal_offset]
            horizontal_offset += 1
            tmp = vertical_offset
            while tmp >= vertical_offset - horizontal_offset:
                if obj == self.__map[tmp][horizontal_offset]:
                    return [tmp, horizontal_offset]
                tmp -= 1
            tmp = vertical_offset
            while tmp <= vertical_offset + horizontal_offset:
                if obj == self.__map[tmp][horizontal_offset]:
                    return [tmp, horizontal_offset]
                tmp += 1
            horizontal_offset += 1
        return []

    def movement_left(self, object_coord: List[int], obj: str, command: List) -> None:
        """
        Move the player to the left.
        :param object_coord:
        :param obj:
        :param command:
        """
        command.append(Movement.LEFT)
        for _ in range(8 - object_coord[0]):
            command.append(Movement.FORWARD)
        command.append(str(Command.TAKE) + obj + "\n")
        command.append(Command.INVENTORY)

    def movement_right(self, object_coord: List[int], obj: str, command: List):
        """
        Move the player to the right.
        :param object_coord:
        :param obj
        :param command:
        """
        command.append(Movement.RIGHT)
        for _ in range(8 - object_coord[0]):
            command.append(Movement.FORWARD)
        command.append(str(Command.TAKE) + obj + "\n")
        command.append(Command.INVENTORY)

    def movement_forward(self, object_coord: List[int], obj: str, command: List):
        """
        Move the player forward.
        :param object_coord:
        :param obj:
        :param command:
        """
        for _ in range(8 - object_coord[1]):
            command.append(Movement.FORWARD)
        command.append(str(Command.TAKE) + obj + "\n")
        command.append(Command.INVENTORY)

    def movement_player(self, look: str, obj: str) -> List:
        """
        Move the player.
        :param look:
        :param obj:
        """
        self.__map = [[]]
        self.create_map(look)
        object_coord: List[int] = self.search_object(obj)
        command: List = []
        if not bool(object_coord):
            command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            return command
        if object_coord[0] == 8 and object_coord[1] == 0:
            return [str(Command.TAKE) + obj + '\n']
        for _ in range(object_coord[0] - 8):
            command.append(Movement.FORWARD)
        if object_coord[0] == 0:
            self.movement_forward(object_coord, obj, command)
        if object_coord[1] == 0:
            command.append(str(Command.TAKE) + obj + "\n")
        if object_coord[0] < 8:
            self.movement_left(object_coord, obj, command)
        if object_coord[0] > 8:
            self.movement_right(object_coord, obj, command)
        return command

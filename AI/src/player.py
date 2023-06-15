"""
Player class is used to store information about the player.
"""
import math
from typing import Dict, List
from enum import Enum
from collections import Counter
import random
import json
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

class Brodcaste(Enum):
    """
    This class is used to store the different broadcast of the player.
    """
    READY = "Brodcast Ready"

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
        self.__shared_inventory: Dict[str, int] = {}
        self.__map: List[List[int]] = [[]]
        self.is_running: bool = True
        self.response: str = ''
        self.__incantation: bool = False
        self.__clear: bool = False
        self.__number_incantation = 0
        self._player_incantation = 0
        self.command: List = []
        self.__step = -2
        self.__ready: bool = False
        self.__direction = 0
        self._message = ''
        self.unused_slots: int = 0
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

    def fill_shared_inventory(self, inventory: str) -> None:
        """
        Fill the shared inventory.
        """
        client, _, inventory = inventory.split(";")
        counter: Dict[str, int] = Counter()
        self.__shared_inventory[client] = json.loads(inventory)
        for obj in self.__shared_inventory:
            if obj == 'total':
                continue
            self.__shared_inventory.update(counter)
        self.__shared_inventory = dict(counter)

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

    def movement_left(self, object_coord: List[int], obj: str) -> None:
        """
        Move the player to the left.
        :param object_coord:
        :param obj:
        :param command:
        """
        self.command.append(Movement.LEFT)
        for _ in range(8 - object_coord[0]):
            self.command.append(Movement.FORWARD)
        self.command.append(str(Command.TAKE) + obj + "\n")
        self.command.append(Command.INVENTORY)

    def movement_right(self, object_coord: List[int], obj: str):
        """
        Move the player to the right.
        :param object_coord:
        :param obj
        :param command:
        """
        self.command.append(Movement.RIGHT)
        for _ in range(8 - object_coord[0]):
            self.command.append(Movement.FORWARD)
        self.command.append(str(Command.TAKE) + obj + "\n")
        self.command.append(Command.INVENTORY)

    def movement_forward(self, object_coord: List[int], obj: str):
        """
        Move the player forward.
        :param object_coord:
        :param obj:
        :param command:
        """
        for _ in range(8 - object_coord[1]):
            self.command.append(Movement.FORWARD)
        self.command.append(str(Command.TAKE) + obj + "\n")
        self.command.append(Command.INVENTORY)

    def movement_player(self, look: str, obj: str) -> List:
        """
        Move the player.
        :param look:
        :param obj:
        """
        self.__map = [[]]
        self.create_map(look)
        object_coord: List[int] = self.search_object(obj)
        if not bool(object_coord):
            self.command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            self.command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            self.command.append(random.choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]))
            return self.command
        if object_coord[0] == 8 and object_coord[1] == 0:
            return [str(Command.TAKE) + obj + '\n']
        for _ in range(object_coord[0] - 8):
            self.command.append(Movement.FORWARD)
        if object_coord[0] == 0:
            self.movement_forward(object_coord, obj)
        if object_coord[1] == 0:
            self.command.append(str(Command.TAKE) + obj + "\n")
        if object_coord[0] < 8:
            self.movement_left(object_coord, obj)
        if object_coord[0] > 8:
            self.movement_right(object_coord, obj)
        return self.command

    def send_movement(self) -> None:
        """
        Send the movement to the server.
        """
        if self.__ready:
            return
        self.command = []
        if self.__direction == 0:
            self._message = str(Brodcaste.READY)
            self.__ready = True
        if self.__direction in (2, 1, 8):
            self.command.append("Forward\n")
        elif self.__direction in (5, 6, 7):
            self.command.append("Right\n")
        else:
            self.command.append("Left\n")

    def brodcast(self, messages_list: List[str]) -> None:
        """
        Brodcast the message.
        :param messages_list:
        :return:
        """
        if "Inventory" in messages_list:
            self.fill_shared_inventory(messages_list[9])
        if "Incantation" in messages_list:
            if self.__clear:
                self.__clear = False
                return
            if self.__step < 4 and self.__step > -1:
                self.__step = 4
                self.command = []
                return
            if self.__number_incantation >= 1:
                self.__number_incantation = 0
                self.__incantation = False
                self.__step = 0
                return
            if self.__incantation:
                self.send_movement()
        if "Ready" in messages_list and self.__number_incantation >= 1:
            self.__number_incantation += 1
        if "Moving" in messages_list:
            self._player_incantation += 1

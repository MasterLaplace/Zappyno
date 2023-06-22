"""
Player class is used to store information about the player.
"""
from json import loads, dumps
from math import sqrt
from random import choice
from re import split
from collections import Counter
from enum import Enum
from typing import Dict, List

separator: str = '|'
required_resources: List[Dict[str, int]] = [
    {'linemate': 1},
    {'linemate': 1, 'deraumere': 1, 'sibur': 1},
    {'linemate': 2, 'sibur': 1, 'phiras': 2},
    {'linemate': 1, 'deraumere': 1, 'sibur': 2, 'phiras': 1},
    {'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3},
    {'linemate': 1, 'deraumere': 2, 'sibur': 3, 'phiras': 1},
    {'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
]

class Movement(Enum):
    """
    This class is used to store the different movement of the player.
    """
    FORWARD = 'Forward'
    LEFT = 'Left'
    RIGHT = 'Right'

class Command(Enum):
    """
    This class is used to store the different command of the player.
    """
    CONNECT_NBR = 'Connect_nbr'
    INVENTORY = 'Inventory'
    BROADCAST = 'Broadcast '
    LOOK = 'Look'
    TAKE = 'Take '
    SET = 'Set '
    INCANTATION = 'Incantation'
    FORK = 'Fork'

class Player:
    """
    This class is used to store information about the player.
    It is used to store the team name, the communication object, the level of the player.
    """
    def __init__(self) -> None:
        self.player_id = 0
        self.__level: int = 1
        self.__inventory: Dict = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0,
            'thystame': 0}
        self.fov: str = ''
        self.__to_take: str = ''
        self.__shared_inventory: Dict = {}
        self.__map: List[List] = [[]]
        self.is_running: bool = True
        self.response: str = ''
        self.__incantation: bool = False
        self.__delete_broadcast: bool = False
        self.delete_read: bool = False
        self.__number_incantation: int = 0
        self.__commands: List = []
        self.step: int = -2
        self.__ready: bool = False
        self.unused_slots: int = 0
        self.fork: bool = True
        self.new_object: bool = False
        self.available_slots: int = 0

    def check_incantation_possible(self) -> bool:
        """
        Check if the incantation is possible.
        """
        for obj in required_resources[self.__level]:
            if self.__shared_inventory[obj] < required_resources[self.__level][obj]:
                return False
        return True

    def drop_object(self) -> None:
        """
        Drop an object.
        :return:
        """
        if self.__commands:
            return
        data = self.fov.split(',')[0]
        while True:
            if len(data) == 0:
                break
            data = data[1:]
        new_data = data.split(' ')
        required = required_resources[self.__level]
        for items in required:
            for res in new_data:
                if res == items:
                    required[items] -= 1
        for ressources in required_resources[self.__level]:
            if ressources in data and data and required[ressources] > 0:
                self.__commands.append(Command.SET.value + ressources)
                self.__commands.append(Command.LOOK.value)
                return
        self.step = 7
        self.response = ''

    def incantation(self) -> None:
        """
        Incantation of the player.
        :return:
        """
        if self.__commands:
            return
        data = self.fov.split(',')[0]
        while True:
            if len(data) == 0:
                break
            data = data[1:]
        new_data = data.split(' ')
        required = required_resources[self.__level].copy()
        for items in required:
            for res in new_data:
                if res == items:
                    required[items] -= 1
        for ressources in required_resources[self.__level]:
            if ressources in data and required[ressources] > 0:
                return
        self.response = Command.INCANTATION.value
        self.__commands = [Command.INCANTATION.value]
        self.step = 7

    def fill_shared_inventory(self, inventory: str) -> None:
        """
        Fill the shared inventory.
        """
        client, _, inventory = inventory.split(separator)
        self.__shared_inventory[client] = loads(inventory)
        self.__shared_inventory[self.player_id] = self.__inventory
        total: Counter = Counter()

        for key, value in self.__shared_inventory.items():
            if key == 'total':
                continue
            total.update(value)
        self.__shared_inventory = dict(total)

    def refresh_shared_inventory(self) -> None:
        """
        Refresh the shared inventory by updating the total value.
        """
        total: Counter = Counter()
        self.__shared_inventory[self.player_id] = self.__inventory

        for key, value in self.__shared_inventory.items():
            if key == 'total':
                continue
            total.update(value)
        self.__shared_inventory['total'] = dict(total)

    def create_map(self) -> None:
        """
        Create a map of the look.
        :param look:
        """
        row_increment = 1
        vertical_offset = 8
        horizontal_offset = 0

        data: list = []
        separated_look: list = self.fov.split(',')
        look_length: int = len(separated_look)
        for i in range(look_length):
            data.append(' '.join(split(r'\'\W+', separated_look[i])[1:]))
        length: int = len(data)
        nb_line: int = int(sqrt(length))
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
        self.__commands.append(Movement.LEFT.value)
        for _ in range(8 - object_coord[0]):
            self.__commands.append(Movement.FORWARD.value)
        self.__commands.append(Command.TAKE.value + obj)
        self.__commands.append(Command.INVENTORY.value)

    def movement_right(self, object_coord: List[int], obj: str):
        """
        Move the player to the right.
        :param object_coord:
        :param obj
        :param command:
        """
        self.__commands.append(Movement.RIGHT.value)
        for _ in range(8 - object_coord[0]):
            self.__commands.append(Movement.FORWARD.value)
        self.__commands.append(Command.TAKE.value + obj)
        self.__commands.append(Command.INVENTORY.value)

    def movement_forward(self, object_coord: List[int], obj: str):
        """
        Move the player forward.
        :param object_coord:
        :param obj:
        :param command:
        """
        for _ in range(8 - object_coord[1]):
            self.__commands.append(Movement.FORWARD.value)
        self.__commands.append(Command.TAKE.value + obj)
        self.__commands.append(Command.INVENTORY.value)

    def execute_action(self) -> None:
        """
        Decide which action to do for the player.
        """
        self.__map = [[[] for _ in range(9)] for _ in range(17)]
        self.create_map()
        object_coord: List[int] = self.search_object(self.__to_take)
        if not bool(object_coord):
            self.__commands.append(choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]).value)
            self.__commands.append(choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]).value)
            self.__commands.append(choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]).value)
            return
        if object_coord[0] == 8 and object_coord[1] == 0:
            self.__commands = [Command.TAKE.value + self.__to_take]
            return
        for _ in range(object_coord[0] - 8):
            self.__commands.append(Movement.FORWARD.value)
        if object_coord[0] == 0:
            self.movement_forward(object_coord, self.__to_take)
        if object_coord[1] == 0:
            self.__commands.append(Command.TAKE.value + self.__to_take)
        if object_coord[0] < 8:
            self.movement_left(object_coord, self.__to_take)
        if object_coord[0] > 8:
            self.movement_right(object_coord, self.__to_take)

    def move_to_broadcasted_tile(self, tile: int) -> None:
        """
        Move to the tile received by the broadcast.
        """
        if self.__commands or self.__ready:
            return
        self.__commands = []
        if tile == 0:
            self.response = Command.BROADCAST.value + 'Ready'
            self.__ready = True
        elif tile in (2, 1, 8):
            self.__commands.append(Movement.FORWARD.value)
        elif tile in (5, 6, 7):
            self.__commands.append(Movement.RIGHT.value)
        else:
            self.__commands.append(Movement.LEFT.value)

    def parse_inventory(self, inventory: str):
        """
        Parse the inventory received by the server and store it in self.__inventory.
        """
        splitted_inventory: List[str] = inventory[1:-1].split(',')

        for elem in splitted_inventory:
            splitted = elem.split()
            if len(splitted) != 2:
                continue
            self.__inventory[splitted[0]] = int(splitted[1])

    def parse_broadcast(self, message: str) -> None:
        """
        Parse the received broadcast message.
        :param message:
        :return:
        """
        from_tile = int(message[8])
        message = message[11:]

        if 'Inventory' in message:
            self.fill_shared_inventory(message[9:])
        if 'Incantation' in message:
            player_id: int = int(message.split(separator)[1])
            if self.__delete_broadcast:
                self.__delete_broadcast = False
                return
            if self.step < 4 and self.step > -1:
                self.step = 4
                self.__commands = []
                return
            if self.__number_incantation >= 1 and player_id > self.player_id:
                self.__incantation = False
                self.__number_incantation = 0
                self.step = 0
                return
            if self.__incantation:
                self.move_to_broadcasted_tile(from_tile)
        if 'Ready' in message and self.__incantation:
            self.__number_incantation += 1

    def find_resource(self) -> str:
        """
        Return a string matching the resource to find.
        The resource is chosen randomly between the missing resources.
        """
        required = required_resources[self.__level].copy()
        missing_resources = []

        if 'total' in self.__shared_inventory:
            inventory = self.__shared_inventory['total'].copy()
        else:
            inventory = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0,
                'thystame': 0}
        for key, value in required.items():
            if value > inventory[key] or key not in inventory:
                missing_resources.append(key)
        if len(missing_resources) == 0:
            return 'food'
        return choice(missing_resources)

    def logical(self) -> None:
        """
        Logical of the AI.
        """
        match self.step:
            case -2:
                return self.__manage_uninitialized()
            case -1:
                return self.__manage_initialized()
            case 0:
                return self.__manage_step_0()
            case 1:
                return self.__manage_step_1()
            case 2:
                return self.__manage_step_2()
            case 3:
                return self.__manage_step_3()
            case 4:
                return self.__manage_step_4()
            case 5:
                return self.__manage_step_5()
            case 6:
                return self.__manage_step_6()
            case 7:
                return self.__manage_step_7()
            case 8:
                return self.__manage_step_8()
            case 9:
                return self.__manage_step_9()
            case 10:
                return self.__manage_step_10()

    def __manage_uninitialized(self) -> None:
        self.response = Command.CONNECT_NBR.value
        self.step = -1

    def __manage_initialized(self) -> None:
        if self.unused_slots > 0:
            self.response = Command.FORK.value
            self.fork = True
        else:
            self.response = Command.LOOK.value
        self.step = 0

    def __manage_step_0(self) -> None:
        if self.__commands:
            self.response = self.__commands[0]
            self.__commands.pop(0)
        else:
            self.response = Command.INVENTORY.value
            self.step = 1

    def __manage_step_1(self) -> None:
        if self.new_object:
            data: List = []
            if not self.check_incantation_possible():
                data = [Command.INCANTATION.value, self.player_id, self.__level]
                self.response = Command.BROADCAST.value + separator.join(str(e) for e in data)
            else:
                data = [Command.INCANTATION.value, self.player_id, self.__level]
                self.__incantation = True
                self.response = Command.BROADCAST.value + separator.join(str(e) for e in data)
                self.step = 4
                self.new_object = False
                return
            self.new_object = False
        else:
            self.step = 2
            self.logical()
            return
        self.step = 2

    def __manage_step_2(self) -> None:
        self.response = Command.LOOK.value
        self.step = 3

    def __manage_step_3(self) -> None:
        self.__to_take = self.find_resource()
        self.execute_action()
        self.step = 0

    def __manage_step_4(self) -> None:
        if not self.__incantation:
            self.__incantation = True
            return
        if self.__number_incantation >= 6:
            self.step = 5
            return
        if self.__number_incantation != 0:
            return
        if len(self.__commands) > 0 and not self.__ready:
            self.response = self.__commands[0]
            self.__commands = self.__commands[1:]
            self.__delete_broadcast = True
            if len(self.__commands) == 0:
                self.delete_read = True
        elif Command.BROADCAST.value in self.response and self.__ready:
            self.step = 5
        else:
            self.response = ''

    def __manage_step_5(self) -> None:
        self.__delete_broadcast = False
        self.response = Command.LOOK.value
        self.step += 1

    def __manage_step_6(self) -> None:
        self.__delete_broadcast = False
        if self.__number_incantation >= 6:
            self.incantation()
        if self.step != 7:
            self.drop_object()
            if len(self.__commands) > 0:
                self.response = self.__commands[0]
                self.__commands = self.__commands[1:]
            else:
                self.response = Command.INVENTORY.value

    def __manage_step_7(self) -> None:
        if self.__number_incantation < 6:
            self.response = Command.CONNECT_NBR.value
            return
        if len(self.__commands) > 0:
            self.response = self.__commands[0]
            self.__commands = self.__commands[1:]
        else:
            self.__commands = [Command.INVENTORY.value, Command.LOOK.value]

    def __manage_step_8(self) -> None:
        self.response = ''

    def __manage_step_9(self) -> None:
        self.response = Command.INVENTORY.value
        self.step = 10

    def __manage_step_10(self) -> None:
        data: List = [Command.INVENTORY.value, self.player_id, self.__level, dumps(self.__inventory)]
        self.response = Command.BROADCAST.value + separator.join(str(e) for e in data)
        self.step = 0

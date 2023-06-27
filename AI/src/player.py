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
from utils import Utils

separator: str = '|'

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
    READY = 'Ready'
    FORK = 'Fork'

class Player:
    """
    This class is used to store information about the player.
    It is used to store the team name, the communication object, the level of the player.
    """
    def __init__(self) -> None:
        self.player_id: int = 0
        self.level: int = 1
        self.__inventory: Dict = Utils.get_default_inventory()
        self.fov: str = ''
        self.__to_take: str = ''
        self.__shared_inventory: Dict[int, Dict[int, Dict[str, int]]] = {}
        self.__map: List[List] = [[]]
        self.is_running: bool = True
        self.response: str = ''
        self.__delete_broadcast: bool = False
        self.delete_read: bool = False
        self.__incantation_count: int = 0
        self.__incanting: bool = False
        self.__commands: List = []
        self.step: int = -2
        self.__ready: bool = False
        self.unused_slots: int = 0
        self.fork: bool = True
        self.got_new_stone: bool = False
        self.available_slots: int = 0

    def __get_total_shared_inventory(self) -> Dict[str, int]:
        """
        Get the total of shared resources for a given level.
        """
        total: Counter = Counter()

        if self.level not in self.__shared_inventory:
            return Utils.get_default_inventory()
        for value in self.__shared_inventory[self.level].values():
            total.update(value)
        return dict(total)

    def __check_incantation_possible(self) -> bool:
        """
        Check if the incantation is possible.
        """
        required: Dict[str, int] = Utils.get_required_resources_for(self.level)
        shared: Dict[str, int] = self.__get_total_shared_inventory()

        for item, quantity in required.items():
            if shared[item] < quantity:
                return False
        return True

    def __set_object(self) -> None:
        """
        Drop an object.
        :return:
        """
        if len(self.__commands) > 0:
            return
        data = self.fov[1:-1].split(',')[0]
        splitted = data.strip().split(' ')
        required = Utils.get_required_resources_for(self.level)
        for item in required:
            for res in splitted:
                if res != item:
                    continue
                required[item] -= 1
        for item, quantity in required.items():
            if quantity == 0 or item not in self.__inventory or self.__inventory[item] == 0:
                continue
            self.__commands += [Command.SET.value + item, Command.LOOK.value, self.__get_shared_inventory_broadcast()]
            self.__inventory[item] -= 1
            return
        # self.step = 7
        self.response = ''

    def __incantation(self) -> None:
        """
        Incantation of the player.
        :return:
        """
        data = self.fov[1:-1].split(',')[0]
        splitted = data.strip().split(' ')
        required = Utils.get_required_resources_for(self.level)

        for item in required:
            for res in splitted:
                if res != item:
                    continue
                required[item] -= 1
        for _, quantity in required.items():
            if quantity == 0:
                continue
            return
        self.response = Command.INCANTATION.value
        self.__commands.clear()
        self.step = 7

    def refresh_shared_inventory(self, level: int, player_id: int) -> None:
        """
        Refresh the shared inventory by updating the total value.
        """
        to_delete = []

        # Adding the current inventory to the shared inventory.

        # Fing the player inventory from the old levels
        for level_inventories_key, level_inventories_value in self.__shared_inventory.items():
            if level_inventories_key == level:
                continue
            for inventory_key in level_inventories_value.keys():
                if inventory_key != player_id:
                    continue
                to_delete.append(level_inventories_key)

        # Delete the inventory from all the old levels.
        for level_to_delete in to_delete:
            del self.__shared_inventory[level_to_delete][player_id]

    def __save_inventory_to_shared(self) -> None:
        if self.level not in self.__shared_inventory:
            self.__shared_inventory[self.level] = {}
        self.__shared_inventory[self.level][self.player_id] = self.__inventory
        self.refresh_shared_inventory(self.level, self.player_id)

    def __fill_shared_inventory(self, inventory: str) -> None:
        """
        Fill the shared inventory.
        """
        args: List[str] = inventory.split(separator)
        client_id: int = int(args[1])
        player_level: int = int(args[2])
        stringified_inventory: str = args[3]

        if player_level not in self.__shared_inventory:
            self.__shared_inventory[player_level] = {}
        self.__shared_inventory[player_level][client_id] = loads(stringified_inventory)
        self.refresh_shared_inventory(int(player_level), int(client_id))
        self.__save_inventory_to_shared()

    def __create_map(self) -> None:
        """
        Create a map of the look.
        :param look:
        """
        field_wideness: int = 1
        field_position: int = 0
        vertical_offset: int = 8
        horizontal_offset: int = 0
        data: List[str] = [' '.join(split('\W+', elem)[1:]) for elem in self.fov.split(',')]
        line: int = int(sqrt(len(data)))

        for _ in range(line):
            row: int = vertical_offset - horizontal_offset
            for _ in range(field_wideness):
                self.__map[row][horizontal_offset].append(data[field_position])
                field_position += 1
                row += 1
            horizontal_offset += 1
            field_wideness += 2

    def array_size(self, array: list) -> int:
        """
        Get the size of the array.
        :param array:
        """
        number = 0

        for elem in array:
            if len(elem) == 0:
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
            if (len(self.__map[vertical_offset][horizontal_offset]) > 0 and
            obj in self.__map[vertical_offset][horizontal_offset][0]):
                return [vertical_offset, horizontal_offset]
            horizontal_offset += 1
            total = vertical_offset
            while total >= vertical_offset - horizontal_offset:
                if (len(self.__map[vertical_offset][horizontal_offset]) > 0 and
                obj in self.__map[total][horizontal_offset][0]):
                    return [total, horizontal_offset]
                total -= 1
            total = vertical_offset
            while total <= vertical_offset + horizontal_offset:
                if (len(self.__map[vertical_offset][horizontal_offset]) > 0 and
                obj in self.__map[total][horizontal_offset][0]):
                    return [total, horizontal_offset]
                total += 1
            horizontal_offset += 1
        return []

    def movement_left(self, object_coord: List[int]) -> None:
        """
        Move the player to the left.
        :param object_coord:
        :param obj:
        :param command:
        """
        self.__commands.append(Movement.LEFT.value)
        for _ in range(8 - object_coord[0]):
            self.__commands.append(Movement.FORWARD.value)

    def movement_right(self, object_coord: List[int]):
        """
        Move the player to the right.
        :param object_coord:
        :param obj
        :param command:
        """
        self.__commands.append(Movement.RIGHT.value)
        for _ in range(object_coord[0] - 8):
            self.__commands.append(Movement.FORWARD.value)

    def movement_forward(self, object_coord: List[int]):
        """
        Move the player forward.
        :param object_coord:
        :param obj:
        :param command:
        """
        for _ in range(8 - object_coord[1]):
            self.__commands.append(Movement.FORWARD.value)

    def __execute_action(self) -> None:
        """
        Decide which action to do for the player.
        """
        self.__map = [[[] for _ in range(9)] for _ in range(17)]
        self.__create_map()
        object_pos: List[int] = self.search_object(self.__to_take)

        if len(object_pos) == 0:
            self.__commands += [choice([Movement.FORWARD, Movement.LEFT, Movement.RIGHT]).value for _ in range(3)]
            return
        for _ in range(object_pos[1]):
            self.__commands.append(Movement.FORWARD.value)
        if object_pos[0] < 8:
            self.movement_left(object_pos)
        elif object_pos[0] > 8:
            self.movement_right(object_pos)
        self.__commands += [Command.TAKE.value + self.__to_take, Command.INVENTORY.value]

    def move_to_broadcasted_tile(self, origin: int) -> None:
        """
        Move to the tile received by the broadcast with the provided origin.
        """
        if self.__commands or self.__ready:
            return
        self.__commands = []
        if origin == 0:
            self.response = Command.BROADCAST.value + Command.READY.value
            self.__ready = True
        elif origin in (2, 1, 8):
            self.__commands.append(Movement.FORWARD.value)
        elif origin in (5, 6, 7):
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
        self.__save_inventory_to_shared()
        print(f'{self.player_id}: Food quantity: {self.__inventory["food"]}')

    def parse_broadcast(self, message: str) -> None:
        """
        Parse the received broadcast message.
        :param message:
        :return:
        """
        from_tile: int = int(message[8])
        cleaned_message: str = message[11:]
        args: List[str] = cleaned_message.split(separator)

        if Command.INVENTORY.value in cleaned_message:
            self.__fill_shared_inventory(cleaned_message[9:])
        if Command.INCANTATION.value in cleaned_message:
            player_id: int = int(args[1])
            player_level: int = int(args[2])

            if self.__delete_broadcast:
                self.__delete_broadcast = False
                return

            if player_level != self.level:
                return

            if self.__incantation_count >= 1 and player_id > self.player_id:
                self.__incanting = False
                self.__incantation_count = 0
                self.step = 0
                return

            if self.step >= 0 and self.step <= 3 and self.__inventory['food'] >= Utils.get_minimum_food_quantity():
                self.step = 4
                self.__commands.clear()
                return

            if self.__incanting:
                self.move_to_broadcasted_tile(from_tile)

        if Command.READY.value in cleaned_message and self.__incantation_count != 0:
            self.__incantation_count += 1

    def find_resource(self) -> str:
        """
        Return a string matching the resource to find.
        The resource is chosen randomly between the missing resources.
        """
        inventory = self.__get_total_shared_inventory()
        required = Utils.get_required_resources_for(self.level)
        missing_resources = []

        for item, quantity in required.items():
            if item not in inventory or quantity > inventory[item]:
                missing_resources.append(item)
        if len(missing_resources) == 0:
            return 'food'
        return choice(missing_resources)

    def level_up(self) -> None:
        """
        Reset some player parameters when level up.
        """
        self.step = 9
        self.got_new_stone = False
        self.__incanting = False
        self.__incantation_count = 0
        self.__ready = False
        self.__delete_broadcast = False
        self.delete_read = False
        self.__to_take = ''

    def __get_shared_inventory_broadcast(self) -> str:
        data: List = [Command.INVENTORY.value, self.player_id, self.level, dumps(self.__inventory)]

        return Command.BROADCAST.value + separator.join(str(e) for e in data)

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
            self.response = ''
            self.fork = True
        self.step = 0

    def __manage_step_0(self) -> None:
        if len(self.__commands) > 0:
            self.response = self.__commands.pop(0)
        else:
            self.response = Command.INVENTORY.value
            self.step = 1

    def __manage_step_1(self) -> None:
        if self.got_new_stone:
            self.got_new_stone = False
            if not self.__check_incantation_possible():
                self.response = self.__get_shared_inventory_broadcast()
            else:
                data: List = [Command.INCANTATION.value, self.player_id, self.level]
                self.response = Command.BROADCAST.value + separator.join(str(e) for e in data)
                self.__incantation_count = 1
                self.__incanting = True
                self.step = 4
                return
        else:
            self.step = 2
            self.logical()
            return
        self.step = 2

    def __manage_step_2(self) -> None:
        self.response = Command.LOOK.value
        self.step = 3

    def __manage_step_3(self) -> None:
        if self.__inventory['food'] < Utils.get_minimum_food_quantity():
            self.__to_take = 'food'
        else:
            self.__to_take = self.find_resource()
        self.__execute_action()
        self.step = 0

    def __manage_step_4(self) -> None:
        if not self.__incanting:
            self.__incanting = True
            return

        if self.__incantation_count >= Utils.get_required_players_for(self.level):
            self.step = 5
            return

        if self.__incantation_count != 0:
            print('WAITING FOR OTHER PLAYERS')
            return

        if len(self.__commands) > 0 and not self.__ready:
            self.response = self.__commands.pop(0)
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
        self.step = 6

    def __manage_step_6(self) -> None:
        self.__delete_broadcast = False
        if Utils.get_required_players_for(self.level) >= self.__incantation_count:
            self.__incantation()
            print('START INCANTATION OR NOT ?')
        if self.step == 7:
            return
        self.__set_object()
        if len(self.__commands) > 0:
            self.response = self.__commands.pop(0)
        else:
            self.response = Command.INVENTORY.value

    def __manage_step_7(self) -> None:
        if len(self.__commands) > 0:
            self.response = self.__commands.pop(0)
        else:
            self.__commands = [Command.INVENTORY.value, Command.LOOK.value]

    def __manage_step_8(self) -> None:
        self.response = ''

    def __manage_step_9(self) -> None:
        self.response = Command.INVENTORY.value
        self.step = 10

    def __manage_step_10(self) -> None:
        self.response = self.__get_shared_inventory_broadcast()
        self.step = 0

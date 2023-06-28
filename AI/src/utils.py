"""
Utils class used to get some useful informations
"""

from typing import Dict, List
from uuid import uuid4

class Utils:
    """
    This class provides some useful methods such as some getters.
    All of them are static.
    """
    @staticmethod
    def get_default_inventory() -> Dict:
        """
        Return the default inventory of a player.
        """
        return {
            'food': 0,
            'linemate': 0,
            'deraumere': 0,
            'sibur': 0,
            'mendiane': 0,
            'phiras': 0,
            'thystame': 0
        }

    @staticmethod
    def get_required_resources_for(level: int) -> Dict[str, int]:
        """
        Get the required resources to incantate for a given level.
        """
        levels: List[Dict[str, int]] = [
            {'linemate': 1},
            {'linemate': 1, 'deraumere': 1, 'sibur': 1},
            {'linemate': 2, 'sibur': 1, 'phiras': 2},
            {'linemate': 1, 'deraumere': 1, 'sibur': 2, 'phiras': 1},
            {'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3},
            {'linemate': 1, 'deraumere': 2, 'sibur': 3, 'phiras': 1},
            {'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
        ]

        return levels[level - 1]

    @staticmethod
    def get_required_players_for(level: int) -> int:
        """
        Get the required players count to incantate for a given level.
        """
        levels: List[int] = [1, 2, 2, 4, 4, 6, 6]

        return levels[level - 1]

    @staticmethod
    def get_minimum_food_quantity() -> int:
        """
        Get the minimum food quantity to survive.
        """
        return 25

    @staticmethod
    def generate_uuid() -> str:
        """
        Generate an uuid.
        """
        return str(uuid4())

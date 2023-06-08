"""
This file is used to create the player
"""
from sys import argv
import sys
from pathfinder_player import PathfinderPlayer
from collector_player import CollectorPlayer
from communication import Communication
from player import Player

def creation_player(communication: Communication) -> Player:
    """
    This function is used to create the player
    :param communication:
    :return:
    """
    player_info = communication.receive()
    if player_info == 'ko':
        print('Invalid team name')
        sys.exit(84)
    if int(player_info[0]) > 6:
        return PathfinderPlayer(communication, argv[2], player_info[1], int(player_info[0]))
    return CollectorPlayer(communication, argv[2], player_info[1], int(player_info[0]))

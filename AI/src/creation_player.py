"""
This file is used to create the player
"""
from sys import argv
import sys
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
    return Player(communication, argv[2], int(player_info[0]))

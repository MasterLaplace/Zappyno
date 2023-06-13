#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This program is an AI for the Zappy project.
You can find more information with ./zappy_ai -h
"""
from sys import argv

from communication import Communication
from creation_player import creation_player
from player import Player

communication: Communication = Communication('localhost', 4242)

if __name__ == '__main__':
    communication.connect()
    communication.receive()
    communication.send(argv[2])
    player: Player = creation_player(communication)
    while True:
        text: str = input('Enter text: ')
        if text == 'exit':
            break
        communication.send(text)
        player.add_inventory()
        player.look()
        player.take_object()
        player.add_inventory()

    communication.disconnect()

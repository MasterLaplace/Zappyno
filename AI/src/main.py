#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This program is an AI for the Zappy project.
You can find more information with ./zappy_ai -h
"""
import sys

from communication import Communication
from player import Player

communication: Communication = Communication('localhost', 4242)

if __name__ == '__main__':
    communication.connect()
    communication.receive()
    communication.send(sys.argv[2])
    player_info = communication.receive()
    if player_info == 'ko':
        print('Invalid team name')
        sys.exit(84)
    Player(communication, sys.argv[2], player_info[1], player_info[0])
    while True:
        text: str = input('Enter text: ')
        if text == 'exit':
            break
        communication.send(text)
        print(communication.receive())
    communication.disconnect()

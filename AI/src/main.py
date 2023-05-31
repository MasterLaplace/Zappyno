#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This program is an AI for the Zappy project.
You can find more information with ./zappy_ai -h
"""
from communication import Communication

communication: Communication = Communication('localhost', 3030)

if __name__ == '__main__':
    communication.connect()
    while True:
        text: str = input('Enter text: ')
        if text == 'exit':
            break
        communication.send(text)
    communication.disconnect()

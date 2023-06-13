#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This program is an AI for the Zappy project.
You can find more information with ./zappy_ai -h
"""
from sys import argv
from communication import Communication
from client import Client

communication: Communication = Communication('localhost', 4243)

if __name__ == '__main__':
    client: Client = Client(argv[1], int(argv[2]), argv[3])
    client.loop()

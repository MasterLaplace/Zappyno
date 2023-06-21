#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This program is an AI for the Zappy project.
You can find more information with ./zappy_ai -h
"""
from argparse import ArgumentParser, Namespace
from sys import exit as sys_exit
from client import Client

def get_arguments() -> ArgumentParser:
    """
    Instanciate the argument parser and add the arguments.
    """
    parser: ArgumentParser = ArgumentParser(add_help=False)

    parser.add_argument('-p', type=int, help='is the port number (between 0 and 65535)', dest='port')
    parser.add_argument('-n', type=str, help='is the name of the team', dest='name')
    parser.add_argument('-h', type=str, help='is the name of the machine; localhost by default', default='localhost',
        dest='host')
    return parser

if __name__ == '__main__':
    arguments: ArgumentParser = get_arguments()

    args: Namespace = arguments.parse_args()
    if not args.port or not args.name or (args.port < 0 or args.port > 65535):
        arguments.print_help()
        sys_exit(1)
    client: Client = Client(args.host, args.port, args.name)
    client.loop()

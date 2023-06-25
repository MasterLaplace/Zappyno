# Zappy AI
## Project Description
The goal of this project is to create a network game. The project is composed of two parts: the server and the AI. Several teams confront on a tiles map containing resources. The winning team is the one with 6 players who reached the highest elevation.  
The AI is a program that will connect to the server and control a team of players. It will have to collect resources, build elevations and fight against other players.

## How to use
```bash
~ > ./zappy_ai –help
USAGE: ./zappy_ai -p port -n name -h machine
    port is the port number
    name is the name of the team
    machine is the name of the machine; localhost by default```
```

## Technical Details
The AI is written in Python. It uses the [socket](https://docs.python.org/3/library/socket.html) library to communicate with the server.  
The protocol used to communicate with the server is described in the [Protocol.pdf](./Protocol.pdf) file.

All AI will be able to communicate (broadcast) with each other to share information by sending them through the server. 
There's 3 broadcast type:
* Moving sent by an AI when moving to an other tile: `moving`
* Ready sent by an AI when once ready to incantate: `ready`
* Incantation sent by an AI when there's enough players on its tile and ready to incantate
* Inventory: all AIs will know each other's inventory status by sharing them: `inventory {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, "thystame": 0}`

Broadcasts will have the following format: `Broadcast PLAYER_TEAM|PLAYER_ID|PLAYER_LEVEL|MESSAGE`
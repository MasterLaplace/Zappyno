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

There'll be 3 AI types:
- An AI that'll be the center of the map and will provide the central vision of the map to the other AIs.
- An AI that'll look for resources and inform the third AI type of the resources location.
- An AI that'll collect the resources and build elevations.

All AI will be able to communicate with each other to share information by sending them through the server.

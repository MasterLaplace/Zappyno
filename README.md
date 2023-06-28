# ME : <p align="center">Zappyno (Zappy)</p>

<p align="center">
    <a href="https://github.com/EpitechPromo2026/B-YEP-400-REN-4-1-zappy-tristan.bros/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge" alt="License: MIT">
    </a><a>
        <img src="https://img.shields.io/badge/C++-17-blue?style=for-the-badge" alt="C++: 17">
    </a><a>
        <img src="https://img.shields.io/badge/C-18-blue?style=for-the-badge" alt="C: 18">
    </a><a>
        <img src="https://img.shields.io/badge/OS-Linux-blue?style=for-the-badge" alt="OS: Linux">
    </a><a>
        <img src="https://img.shields.io/badge/SFML-2.5-blue?style=for-the-badge" alt="SFML: 2.5">
    </a>
</p>

Status: in progress


## :placard: Table of Contents
- [Description](#description)
- [Running](#running)
- [Tree](#tree)
- [License](#license)
- [Contacts](#contacts)


<div id='description'/>

## :pencil: **DESCRIPTION**

The goal of this project is to create a network game where several teams confront on a tiles map containing
resources.
The winning team is the first one where at least 6 players who reach the maximum elevation.

Zappy is an interesting project that integrates concepts from networking, multi-threading, and AI into a competitive game environment.

- Part 1: The Game Environment and Rules At its core, Zappy is a resource gathering game played on a grid map. The map contains various resources and the game includes several teams, each composed of players referred to as Trantorians. The primary goal is for these Trantorians to gather enough resources and evolve to the highest level. They evolve by conducting incantations, which require a specific quantity of each resource and a certain number of Trantorians at the same level. The first team to elevate a Trantorian to the highest level wins the game.

- Part 2: The Networking and Multi-threading To create a live gaming experience, Zappy uses a client-server architecture, with the server handling the main game logic and maintaining the game state. Trantorians are managed by AI clients, which connect to the server and send commands representing the actions of their Trantorian. The server, in return, sends updates about the game state. The server must be capable of handling multiple clients at once, requiring the use of multi-threaded programming.

- Part 3: The AI The Trantorians in Zappy are controlled by AI. This AI decides what actions the Trantorians should take based on the current state of the game. This could involve gathering resources, conducting an incantation, or interacting with other Trantorians. It's this AI element that makes Zappy a fascinating project: beyond the technical challenges of building the game server, participants can also dive into the complexities of creating an AI strategy to win the game.Thus, Zappy is not just about building a server—it's about creating a competitive environment where AI strategies can be put to the test.


<div id='running'/>

## :truck: **RUNNING**

```shell
# Clone repository
$ git clone git@github.com:EpitechPromo2026/B-YEP-400-REN-4-1-zappy-tristan.bros.git
$ cd B-YEP-400-REN-4-1-zappy-tristan.bros

# Dependencies
$ make

# Run Zappy Server
$ ./zappy_server –help

# Run Zappy Gui
$ ./zappy_gui –help

# Run Zappy AI
$ ./zappy_ai –help

# Run tests
$ make tests_run

# Clean
$ make clean
```

### INTERACTIONS

| Key | Action |
| --- | --- |
| <kbd>`...`</kbd> | ... |
| <kbd>`ESC`</kbd> | Quit |
| <kbd>`F1`</kbd>  | Pause Music |
| <kbd>`UP`</kbd>/<kbd>`Z`</kbd>  | Move up |
| <kbd>`RIGHT`</kbd>/<kbd>`D`</kbd> | Move right |
| <kbd>`DOWN`</kbd>/<kbd>`S`</kbd> | Move down |
| <kbd>`LEFT`</kbd>/<kbd>`Q`</kbd> | Move left |
| <kbd>`Scroll`</kbd> | Zoom |


<div id='tree'>

## :evergreen_tree: **TREE**

```shell
.
├── AI                                # AI client code
│   ├── Docs
│   ├── include
│   ├── src
│   └── tests
├── B-YEP-400-zappy
├── Docs                              # Documentation directory
├── GUI                               # GUI code
│   ├── Docs
│   ├── includes
│   ├── Install
│   ├── obj
│   ├── Script
│   ├── src
│   │   ├── Core
│   │   ├── Engine
│   │   ├── Interface
│   │   ├── Manager
│   │   └── Utils
│   │       ├── Math
│   │       ├── Parser
│   │       └── String
│   └── tests
├── __MACOSX
│   └── Zappy
│       └── Docs
└── Server                            # Server code
    ├── Docs
    ├── include
    ├── src
    │   ├── commands
    │   ├── game_logic
    │   ├── network
    │   └── thread_logic
    └── tests
```

## :wrench: More help

Here's more documentation about the project

* [Technical documentation [PDF]](Docs/technical.pdf)
* [Technical documentation](Docs/Zappy/html/index.html)


<div id='license'/>

## :scroll: **LICENSE**

This project is licensed under the terms of the [MIT License](./LICENSE).

Copyright © 2023-2024 :

[Master_Laplace](https://github.com/MasterLaplace),

[M7T5M3P](https://github.com/M7T5M3P),

[MathieuCouronne](https://github.com/MathieuCouronne),

[RaphaelLecoq](https://github.com/RaphaelLecoq),

[mlbonniec](https://github.com/mlbonniec),

[Tristanepitech](https://github.com/Tristanepitech).


<div id='contacts'/>

## :mailbox_with_mail: **CONTACTS**

This project has been carried out by:

* [![GitHub Master_Laplace](https://img.shields.io/github/followers/MasterLaplace?label=MasterLaplace&style=social)](https://github.com/MasterLaplace)
* [![GitHub Mathys T](https://img.shields.io/github/followers/M7T5M3P?label=MathysT&style=social)](https://github.com/M7T5M3P)
* [![Mathis LE BONNIEC](https://img.shields.io/github/followers/mlbonniec?label=mlbonniec&style=social)](https://github.com/mlbonniec)
* [![Mathieu Couronne](https://img.shields.io/github/followers/MathieuCouronne?label=MathieuCouronne&style=social)](https://github.com/MathieuCouronne)
* [![Raphaël LECOQ](https://img.shields.io/github/followers/RaphaelLecoq?label=RaphaelLecoq&style=social)](https://github.com/RaphaelLecoq)
* [![GitHub Tristanepitech](https://img.shields.io/github/followers/Tristanepitech?label=Tristanepitech&style=social)](https://github.com/Tristanepitech)

---
<p align="center">ME.inc</p>

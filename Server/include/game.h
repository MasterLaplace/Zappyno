/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** game.h
*/

#ifndef GAME_H_
#define GAME_H_

//Include all the libraries you need here
#include <stdio.h>
#include <string.h>

typedef struct s_client t_client;
typedef struct s_server t_server;

typedef struct s_teams {
    char *name;
    t_client *players;
    int nb_players;
} t_teams;

typedef struct s_inventory {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} t_inventory;

typedef struct s_tiles {
    int x;
    int y;
    t_inventory *inventory;
} t_tiles;

typedef struct s_game {
    t_teams *teams;
    t_client *current_client;
    t_tiles **tiles;
    // TODO: Add more structures as needed...
} t_game;

typedef struct s_command {
    char *command_id;
    void (*function)(t_server *, char **);
} t_command;
#endif /* !GAME_H_ */
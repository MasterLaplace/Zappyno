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
    int max_players;
} t_teams;

typedef struct t_map {
    int x;
    int y;
    int resources[TOTAL_RESOURCES];
    int player;
    int egg;
} t_map;

typedef struct s_game {
    t_teams *teams;
    t_map *tiles;
} t_game;

typedef struct gui_command {
    char *command_id;
    void (*function)(t_server *, char **);
} gui_command;

typedef struct ai_command {
    char *command_id;
    void (*function_ai)(t_server *, char **);
} ai_command;
#endif /* !GAME_H_ */
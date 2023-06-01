/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** game.h
*/

#ifndef GAME_H_
#define GAME_H_

//Include all the libraries you need here
#include "client.h"
#include "params.h"
#include "server.h"

typedef struct s_game {
    t_params params;
    int client_count;
    int map_width;
    int map_height;
    // TODO: Add more structures as needed...
} t_game;

typedef void (*t_command_func)(t_game *, char *);

typedef struct s_command {
    char *name;
    t_command_func function;
} t_command;

// Declare commands here
// msz : map size
void msz(t_game *game, char *args);

#endif /* !GAME_H_ */
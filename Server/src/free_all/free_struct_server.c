/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../../include/server.h"

void free_double_array(char ***array)
{
    char **arr = *array;

    if (!arr)
        return;
    for (unsigned i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

static void free_game(t_game *game)
{
    if (!game)
        return;
    if (game->teams) {
        for (int i = 0; game->teams[i].name; i++)
            free(game->teams[i].name);
    }
    if (game->tiles) {
        for (int i = 0; game->teams[i].players; i++)
            free(game->teams[i].players);
    }
    if (game->teams)
        free(game->teams);
    if (game->tiles)
        free(game->tiles);
}

static void free_params(t_params *params)
{
    if (params) {
        for (int i = 0; params->team_names[i]; i++)
            free(params->team_names[i]);
    }
    if (params->team_names)
        free(params->team_names);
}

void free_server(t_server **server)
{
    t_server *serv = *server;

    if (!serv)
        return;
    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (serv->clients[i].buffer)
            free(serv->clients[i].buffer);
        if (serv->clients[i].params_function)
            free_double_array(&serv->clients[i].params_function);
    }
    if (serv->params)
        free_params(serv->params);
    free_game(&serv->game);
}

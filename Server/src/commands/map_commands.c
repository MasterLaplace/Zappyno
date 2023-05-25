/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../include/game.h"

void msz(t_game *game, char *args) {
    (void)args;

    char response[128];
    sprintf(response, "msz %d %d\n", game->map_width, game->map_height);

    //send_to_client(game->clients, response);
}

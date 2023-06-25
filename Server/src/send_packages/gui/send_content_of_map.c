/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** content_of_map
*/

#include "../../../include/send_package.h"

static unsigned size_content_map(t_server *server)
{
    unsigned size = 0;
    int map_size = server->params->width * server->params->height - 1;
    for (int i = 0; i < map_size; i++) {
        size += my_nblen(server->game.tiles[i].x) +
        my_nblen(server->game.tiles[i].y) +
        my_nblen(server->game.tiles[i].resources[0]) +
        my_nblen(server->game.tiles[i].resources[1]) +
        my_nblen(server->game.tiles[i].resources[2]) +
        my_nblen(server->game.tiles[i].resources[3]) +
        my_nblen(server->game.tiles[i].resources[4]) +
        my_nblen(server->game.tiles[i].resources[5]) +
        my_nblen(server->game.tiles[i].resources[6]) + 14;
    }
}

void send_content_of_map(t_server *server, __attribute__((unused)) char **array)
{
    int size = size_content_map(server);
    int map_size = server->params->width * server->params->height - 1;
    AUTO_FREE char *message = calloc(size, sizeof(char));
    AUTO_FREE char *buffer = calloc(size, sizeof(char));
    for (int i = map_size; i >= 0; i--) {
        sprintf(buffer, "bct %d %d %d %d %d %d %d %d %d\n",
                server->game.tiles[i].x,
                server->game.tiles[i].y,
                server->game.tiles[i].resources[0],
                server->game.tiles[i].resources[1],
                server->game.tiles[i].resources[2],
                server->game.tiles[i].resources[3],
                server->game.tiles[i].resources[4],
                server->game.tiles[i].resources[5],
                server->game.tiles[i].resources[6]
        );
        message = my_strcat(message, buffer);
    }
    send_to_gui(server, message, server->id);
}
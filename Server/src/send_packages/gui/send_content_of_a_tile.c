/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** content_of_a_tile
*/

#include "../../../include/send_package.h"

void send_content_of_a_tile(t_server *server, char **array)
{
    if (array[1] == NULL || array[2] != NULL) {
        send_to_client(server, "sbp\n", server->id);
        return;
    }
    int index = atoi(array[1]);
    if (index < 0 || index > server->params->width * server->params->height) {
        send_to_client(server, "sbp\n", server->id);
        return;
    }
    int size = my_nblen(server->game.tiles[index].x) +
        my_nblen(server->game.tiles[index].y) +
        my_nblen(server->game.tiles[index].resources[0]) +
        my_nblen(server->game.tiles[index].resources[1]) +
        my_nblen(server->game.tiles[index].resources[2]) +
        my_nblen(server->game.tiles[index].resources[3]) +
        my_nblen(server->game.tiles[index].resources[4]) +
        my_nblen(server->game.tiles[index].resources[5]) +
        my_nblen(server->game.tiles[index].resources[6]) + 14;
    AUTO_FREE char *message = calloc(size, sizeof(char));
    sprintf(message, "bct %d %d %d %d %d %d %d %d %d\n", server->game.tiles[index].x,
        server->game.tiles[index].y, server->game.tiles[index].resources[0],
        server->game.tiles[index].resources[1], server->game.tiles[index].resources[2],
        server->game.tiles[index].resources[3], server->game.tiles[index].resources[4],
        server->game.tiles[index].resources[5], server->game.tiles[index].resources[6]);
    send_to_gui(server, message, server->id);
}
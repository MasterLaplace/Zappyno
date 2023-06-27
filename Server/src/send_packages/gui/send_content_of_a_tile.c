/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** content_of_a_tile
*/

#include "../../../include/send_package.h"

static int check_param(t_server *server, char **array, int id)
{
    if (array[1] == NULL || array[2] != NULL) {
        send_to_client(server, "sbp\n", id);
        return -1;
    }
    int index = atoi(array[1]);
    if (index < 0 || index > server->params->width * server->params->height) {
        send_to_client(server, "sbp\n", id);
        return -1;
    }
    return index;
}

static int calc_size(t_server *server, int index)
{
    int size = my_nblen(server->game.tiles[index].x) +
my_nblen(server->game.tiles[index].y) +
my_nblen(server->game.tiles[index].resources[0]) +
my_nblen(server->game.tiles[index].resources[1]) +
my_nblen(server->game.tiles[index].resources[2]) +
my_nblen(server->game.tiles[index].resources[3]) +
my_nblen(server->game.tiles[index].resources[4]) +
my_nblen(server->game.tiles[index].resources[5]) +
my_nblen(server->game.tiles[index].resources[6]) + 14;
    return size;
}

void send_content_of_a_tile(t_server *server, char **array, int id)
{
    int ind = 0;
    if ((ind = check_param(server, array, id)) == -1)
        return;
    int size = calc_size(server, ind);
    AUTO_FREE char *message = calloc(size, sizeof(char));
    if (!message)
        return;
    sprintf(message, "bct %d %d %d %d %d %d %d %d %d\n",
server->game.tiles[ind].x, server->game.tiles[ind].y,
server->game.tiles[ind].resources[0], server->game.tiles[ind].resources[1],
server->game.tiles[ind].resources[2], server->game.tiles[ind].resources[3],
server->game.tiles[ind].resources[4], server->game.tiles[ind].resources[5],
server->game.tiles[ind].resources[6]);
    send_to_gui(server, message, id);
}

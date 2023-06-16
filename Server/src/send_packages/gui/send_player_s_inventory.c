/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s
*/

#include "../../../include/send_package.h"

size_t count_inv_size(int *resources, int x, int y, int id)
{
    size_t count = 0;

    for (int i = 0; i != 7; i++)
        count += my_nblen(resources[i]);
    return count + my_nblen(x) + my_nblen(y) + my_nblen(id);
}

void send_player_s_inventory(t_server *server, char** array)
{
    int id = atoi(array[1]);
    int data = 0;
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    AUTO_FREE char *message = calloc(14 + count_inv_size(server->clients[id].resources,
    x, y, id), sizeof(char));
    strncat(message, "pin ",strlen(message) + 4);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x), strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y), strlen(message) + my_nblen(y));
    strncat(message, " ",strlen(message) + 1);
    for (size_t i = 0; i != 7; i++) {
        data = server->game.teams->players[server->id].resources[i];
        strncat(message, itoa(data), strlen(message) + my_nblen(data));
        strncat(message, " ",strlen(message) + 1);
    }
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_player_s_inventory_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    int data = 0;
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    AUTO_FREE char *message = calloc(14 + count_inv_size(server->clients[id].resources,
    x, y, id), sizeof(char));
    strncat(message, "pin ",strlen(message) + 4);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x), strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y), strlen(message) + my_nblen(y));
    strncat(message, " ",strlen(message) + 1);
    for (size_t i = 0; i != 7; i++) {
        data = server->game.teams->players[server->id].resources[i];
        strncat(message, itoa(data), strlen(message) + my_nblen(data));
        strncat(message, " ",strlen(message) + 1);
    }
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

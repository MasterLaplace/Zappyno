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

char *make_inv_message(t_server *server, int id)
{
    int data = 0;
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    char *message = calloc(16 + count_inv_size(server->clients[id].resources,
    x, y, id), sizeof(char));
    sprintf(message, "pin %d %d %d ", id, x, y);
    printf("coucou1\n");
    for (size_t i = 0; i != 7; i++) {
        data = server->game.teams->players[server->id].resources[i];
        strncat(message, itoa(data), strlen(message) + my_nblen(data));
        strncat(message, " ", strlen(message) + 1);
    }
    printf("coucou2\n");
    strncat(message, "\n", strlen(message) + 1);
    printf("coucou3\n");
    return message;
}

void send_player_s_inventory(t_server *server, char** array)
{
    int id = atoi(array[1]);
    char *message;

    if (is_connected_player(server, id)) {
        message = make_inv_message(server, id);
        send_to_client(server, message, server->id);
    } else {
        send_command_paramater(server);
    }
    free(message);
}

void send_player_s_inventory_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    char *message;

    if (is_connected_player(server, id)) {
        message = make_inv_message(server, id);
        send_to_all_clients(server, message);
    } else {
        send_command_paramater_to_all(server);
    }
        (message);
}

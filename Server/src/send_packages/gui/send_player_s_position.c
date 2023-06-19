/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_position
*/

#include "../../../include/send_package.h"

char *make_pos_message(t_server *server, int id)
{
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    int O = server->game.teams->players[id].orientation;
    char *message = calloc(9 + my_nblen(x) + my_nblen(y) + my_nblen(id) +
                                     my_nblen(O), sizeof(char));
    strncat(message, "ppo ",strlen(message) + 4);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x),strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y),strlen(message) + my_nblen(y));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(O),strlen(message) + my_nblen(O));
    sprintf(message, "%s\n", message);
    return message;
}

void send_player_s_position(t_server *server, char** array)
{
    int id = atoi(array[1]);
    char *message;

    if (is_connected_player(server, id)) {
        message = make_pos_message(server, id);
        send_to_client(server, message, server->id);
    } else {
        send_command_paramater(server);
    }
    free(message);
}

void send_player_s_position_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    char *message;

    if (is_connected_player(server, id)) {
        message = make_pos_message(server, id);
        send_to_all_clients(server, message);
    } else {
        send_command_paramater_to_all(server);
    }
    free(message);
}

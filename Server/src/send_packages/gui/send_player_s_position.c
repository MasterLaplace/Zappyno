/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_position
*/

#include "../../../include/send_package.h"

void send_player_s_position(t_server *server, char** array)
{
    int id = atoi(array[1]);
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    int O = server->game.teams->players[id].orientation;
    char *message = calloc(8 + my_nblen(x) + my_nblen(y) + my_nblen(id) +
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
    send_to_client(server, message, id);
    free(message);
}

void send_player_s_position_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    int O = server->game.teams->players[id].orientation;
    AUTO_FREE char *message = calloc(8 + my_nblen(x) + my_nblen(y) + my_nblen(id) +
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
    send_to_client(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_connection_for_an_egg
*/

#include "../../../include/send_package.h"

void send_player_connection_for_an_egg(t_server *server, int egg_num)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + my_nblen(egg_num),
    sizeof(char));
    strncat(message, "ebo ",strlen(message) + 4);
    strncat(message, itoa(egg_num),strlen(message) + my_nblen(egg_num));
    strncat(message, " ",strlen(message) + 1);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_player_connection_for_an_egg_to_all(t_server *server, int egg_num)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + my_nblen(egg_num),
    sizeof(char));
    strncat(message, "ebo ",strlen(message) + 4);
    strncat(message, itoa(egg_num),strlen(message) + my_nblen(egg_num));
    strncat(message, " ",strlen(message) + 1);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

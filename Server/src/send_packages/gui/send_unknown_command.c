/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_unknown_command
*/

#include "../../../include/send_package.h"

void send_unknown_command(t_server *server, int egg_num)
{
    AUTO_FREE char *message = calloc(5 + my_nblen(egg_num),
    sizeof(char));
    strncat(message, "suc",strlen(message) + 3);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_unknown_command_to_all(t_server *server, int egg_num)
{
    AUTO_FREE char *message = calloc(5 + my_nblen(egg_num),
    sizeof(char));
    strncat(message, "suc",strlen(message) + 3);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

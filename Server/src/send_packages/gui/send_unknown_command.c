/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_unknown_command
*/

#include "../../../include/send_package.h"

void send_unknown_command(t_server *server)
{
    AUTO_FREE char *message = calloc(5,sizeof(char));
    sprintf(message, "suc\n");
    send_to_client(server, message, server->id);
}

void send_unknown_command_to_all(t_server *server)
{
    AUTO_FREE char *message = calloc(5,sizeof(char));
    sprintf(message, "suc\n");
    send_to_client(server, message, server->id);
}

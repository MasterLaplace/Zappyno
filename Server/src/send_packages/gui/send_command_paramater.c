/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_unknown_command
*/

#include "../../../include/send_package.h"

void send_command_paramater(t_server *server)
{
    AUTO_FREE char *message = calloc(6,
    sizeof(char));
    strncat(message, "sdp",strlen(message) + 3);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_command_paramater_to_all(t_server *server)
{
    AUTO_FREE char *message = calloc(6,
    sizeof(char));
    strncat(message, "sdp",strlen(message) + 3);
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

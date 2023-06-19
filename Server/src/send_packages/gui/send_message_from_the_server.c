/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_message_from_the_server
*/

#include "../../../include/send_package.h"

void send_message_from_the_server(t_server *server, char *message_)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + strlen(message_),
    sizeof(char));
    strncat(message, "smg ",strlen(message) + 4);
    strncat(message, message_,strlen(message) + strlen(message_));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_message_from_the_server_to_all(t_server *server, char *message_)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + strlen(message_),
    sizeof(char));
    strncat(message, "smg ",strlen(message) + 4);
    strncat(message, message_,strlen(message) + strlen(message_));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

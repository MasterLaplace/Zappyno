/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../include/send_package.h"

void send_map_size(t_server *server)
{
    char *message = calloc(100, sizeof(char));
    sprintf(message, "msz %d %d\n", server->params->width, server->params->height);
    send_to_client(server, message, server->id);
    free(message);
}

void send_map_size_to_all(t_server *server)
{
    char *message = calloc(100, sizeof(char));
    sprintf(message, "msz %d %d\n", server->params->width, server->params->height);
    send_to_all_clients(server, message);
    free(message);
}

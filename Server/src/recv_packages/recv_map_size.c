/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_map_size.c
*/

#include "../../include/send_package.h"

void recv_map_size(t_server *server, char **message)
{
    server->params->width = atoi(message[1]);
    server->params->height = atoi(message[2]);
    if (server->params->width != atoi(message[1]) || server->params->height != atoi(message[2]))
        send_map_size_to_all(server);
}

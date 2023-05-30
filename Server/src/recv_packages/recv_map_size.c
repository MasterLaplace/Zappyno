/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_map_size.c
*/

#include "../../include/send_package.h"

void recv_map_size(t_server *server, u_int8_t *buffer)
{
    MapSize mapsize_t = *(MapSize *) &buffer[sizeof(Package_t)];
    server->params->width = mapsize_t.x;
    server->params->height = mapsize_t.y;
    if (server->params->width != mapsize_t.x || server->params->height != mapsize_t.y)
        send_map_size_to_all(server);
}

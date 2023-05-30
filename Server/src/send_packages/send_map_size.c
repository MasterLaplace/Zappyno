/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../include/send_package.h"

static MapSize set_MapSize_struct(int x, int y)
{
    MapSize mapsize;
    mapsize.x = x;
    mapsize.y = y;
    return mapsize;
}

void send_map_size(t_server *server)
{
    MapSize mapsize = set_MapSize_struct(server->params->width, server->params->height);
    Package_t package;
    package.command_id = MAP_SIZE;
    package.size = htons(sizeof(MapSize));
    send_to_client(&server->clients[server->id], &package, &mapsize, sizeof(MapSize));
}

void send_map_size_to_all(t_server *server)
{
    Package_t package;
    MapSize mapsize = set_MapSize_struct(server->params->width, server->params->height);
    package.command_id = MAP_SIZE;
    package.size = htons(sizeof(MapSize));
    send_to_all_clients(server->clients, &package, &mapsize, sizeof(MapSize));
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** find_tile.c
*/

#include "../../include/server.h"

/**
 * @file find_tile.c
 * @param server
 * @param x
 * @param y
 * @return
 */
int find_tile(t_server *server, int x, int y)
{
    int size = server->params->height * server->params->width;
    for (int i = 0; i < size; i++) {
        if (server->game.tiles[i].x == x && server->game.tiles[i].y == y)
            return i;
    }
    return -1;
}
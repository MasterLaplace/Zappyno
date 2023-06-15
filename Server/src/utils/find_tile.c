/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** find_tile.c
*/

#include "../../include/server.h"

/**
 * @file find_tile.c
 *
 * @param server
 * @param x
 * @param y
 * @return
 */
unsigned find_tile(t_server *server, unsigned x, unsigned y)
{
    unsigned size = server->params->height * server->params->width;
    for (unsigned i = 0; i < size; i++) {
        if (TILES(i).x == x && TILES(i).y == y)
            return i;
    }
    return -1;
}

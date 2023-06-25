/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** find_tile.c
*/

#include "../../include/server.h"
#include "../../include/send_package.h"

/**
 * @file find_tile.c
 *
 * @param server
 * @param x
 * @param y
 * @return
 */
unsigned find_tile(t_server *server, unsigned x, unsigned y, int id)
{
    unsigned size = server->params->height * server->params->width;
    for (unsigned i = 0; i < size; i++) {
        if (TILES(i).x == x && TILES(i).y == y)
            return i;
    }
    return -1;
}

/**
 * @file find_tile.c
 * @param server
 * @param id
 * @param i
 * @return
 */
static tmp_t find_in_teams_next(t_server *server, int id, int i)
{
    tmp_t tmp = {-1, -1};
    for (unsigned j = 0; j < server->game.teams[i].max_players; j++) {
        if (TEAMS[i].players[j].id == id) {
            tmp.i = i;
            tmp.j = j;
            return tmp;
        }
    }
    return tmp;
}

/**
 * @file find_tile.c
 *
 * @param server
 * @param id
 * @return
 */
tmp_t find_in_teams(t_server *server, int id)
{
    tmp_t tmp = {0, 0};
    for (unsigned i = 0; i < server->params->num_teams; i++) {
        tmp = find_in_teams_next(server, id, i);
        if (tmp.j != -1 && tmp.i != -1)
            return tmp;
    }
    return tmp;
}

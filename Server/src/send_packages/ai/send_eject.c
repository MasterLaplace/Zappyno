/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_eject.c
*/

#include "../../../include/send_package.h"

static bool send_message_eject(t_server *server, t_client *client, unsigned i,
    int id)
{
    char *message = calloc(my_nblen(client->id) + 10, sizeof(char));
    if (!message)
        return send_error(server, 0, id), false;
    sprintf(message, "pex %d\n", client->id);
    send_to_client(server, message, i);
    free(message);
    return true;
}

static bool check_for_eject(t_server *server, unsigned target_x,
    unsigned target_y, int id)
{
    bool eject = false;

    for (unsigned i = 0; i < SOMAXCONN; i++) {
        t_client *client = &CLIENT(i);
        if (client->index_team != TEAM_INDEX &&
            client->pos_x == TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x &&
            client->pos_y == TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y) {
            eject &= send_message_eject(server, client, i, id);
        }
    }
    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (TEAMS[TEAM_INDEX].players[i].pos_x == target_x &&
TEAMS[TEAM_INDEX].players[i].pos_y == target_y && CLIENT(i).is_an_egg) {
            send_death_of_an_egg(server, id);
            remove_client(server, id);
        }
    }
    return eject;
}

void send_eject(t_server *server, int id)
{
    unsigned x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    unsigned y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    unsigned target_y = y, target_x = x;
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;

    switch (orientation) {
        case NORTH: target_y = wrap_y(y - 1, server->params->height); break;
        case EAST: target_x = wrap_x(x + 1, server->params->width); break;
        case SOUTH: target_y = wrap_y(y + 1, server->params->height); break;
        case WEST: target_x = wrap_x(x - 1, server->params->width); break;
    }
    if (!check_for_eject(server, target_x, target_y, id))
        send_error(server, 0, id);
    else
        send_to_client(server, "ok\n", id);
}

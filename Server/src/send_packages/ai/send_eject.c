/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_eject.c
*/

#include "../../../include/send_package.h"

static bool check_for_eject(t_server *server, int orientation, int target_x,
int target_y)
{
    bool eject = false;
    for (int i = 0; i < SOMAXCONN; i++) {
        t_client *client = &CLIENT(i);
        if (client->index_team != TEAM_INDEX &&
            client->pos_x == TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x &&
            client->pos_y == TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y) {
            eject = true;
            char *message = calloc(my_nblen(client->id) + 10, sizeof(char));
            sprintf(message, "pex %d\n", client->id);
            send_to_client(server, message, i);
            free(message);
        }
    }
    for (int i = 0; i < SOMAXCONN; i++) {
        if (TEAMS[TEAM_INDEX].players[i].pos_x == target_x &&
TEAMS[TEAM_INDEX].players[i].pos_y == target_y && CLIENT(i).is_an_egg) {
            send_death_of_an_egg(server, server->id);
            remove_client(server, server->id);
        }
    }
    return eject;
}

void send_eject(t_server *server)
{
    int x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int target_y = y, target_x = x;
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    bool eject = false;
    switch (orientation) {
        case NORTH: target_y = wrap_y(y - 1, server->params->height); break;
        case EAST: target_x = wrap_x(x + 1, server->params->width); break;
        case SOUTH: target_y = wrap_y(y + 1, server->params->height); break;
        case WEST: target_x = wrap_x(x - 1, server->params->width); break;
    }
    eject = check_for_eject(server, orientation, target_x, target_y);
    if (!eject)
        send_error(server, 0);
    else
        send_to_client(server, "ok\n", server->id);
}

void send_eject_to_all(t_server *server)
{

}

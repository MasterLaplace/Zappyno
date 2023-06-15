/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_left.c
*/

#include "../../../include/send_package.h"

static void modify_direction(t_server *server)
{
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    switch (orientation) {
        case 0:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 3;
            break;
        case 1:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 0;
            break;
        case 2:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 1;
            break;
        case 3:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 2;
            break;
    }
}

void send_left(t_server *server)
{
    modify_direction(server);
    send_to_client(server, "ok\n", server->id);
}

void send_left_to_all(t_server *server)
{
    modify_direction(server);
    send_to_all_clients(server, "ok\n");
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_right.c
*/

#include "../../../include/send_package.h"

static void modify_direction(t_server *server, int id)
{
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;

    switch (orientation) {
        case 1:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 2;
            break;
        case 2:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 3;
            break;
        case 3:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 4;
            break;
        case 4:
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 1;
            break;
    }
}

void send_right(t_server *server, int id)
{
    modify_direction(server, id);
    send_to_client(server, "ok\n", id);
}

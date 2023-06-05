/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_left.c
*/

#include "../../../include/send_package.h"

static void modify_direction(t_server *server)
{
    int orientation = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    switch (orientation) {
        case 0: // North
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 3; // becomes West
            break;
        case 1: // East
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 0; // becomes North
            break;
        case 2: // South
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 1; // becomes East
            break;
        case 3: // West
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation = 2; // becomes South
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

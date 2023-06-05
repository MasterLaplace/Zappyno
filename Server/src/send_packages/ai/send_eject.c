/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_eject.c
*/

#include "../../../include/send_package.h"

void send_eject(t_server *server)
{
    int x = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int orientation = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    bool eject = false;

    // Determine the coordinates of the target tile in the specified direction
    int target_x = x;
    int target_y = y;
    switch (orientation) {
        case NORTH: target_y = wrap_y(y - 1, server->params->height); break;
        case EAST: target_x = wrap_x(x + 1, server->params->width); break;
        case SOUTH: target_y = wrap_y(y + 1, server->params->height); break;
        case WEST: target_x = wrap_x(x - 1, server->params->width); break;
    }

    // Find the players on the target tile and eject them
    for (int i = 0; i < MAX_CLIENTS; i++) {
        t_client *client = &server->clients[i];
        printf("client_posx: %d, client_posy: %d | team_posx: %d, team_posy: %d | index_team : %d, TEAM_INDEX : %d\n", client->pos_x, client->pos_y, server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x, server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y, client->index_team, TEAM_INDEX);
        if (client->index_team != TEAM_INDEX &&
            client->pos_x == server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x &&
            client->pos_y == server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y) {
            eject = true;
            char message[12];
            sprintf(message, "eject : %d\n", orientation);
            send_to_client(server, message, i);
        }
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->game.teams[TEAM_INDEX].players[i].pos_x == target_x &&
            server->game.teams[TEAM_INDEX].players[i].pos_y == target_y &&
            server->clients[i].is_an_egg == true) {
            remove_client(server, server->id);
        }
    }
    if (!eject)
        send_error(server, 0);
    else
        send_to_client(server, "ok\n", server->id);
}

void send_eject_to_all(t_server *server)
{

}
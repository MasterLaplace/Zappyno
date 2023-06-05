/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_forward.c
*/

#include "../../../include/send_package.h"

void modify_position(t_server *server) {
    int x = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int orientation = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    int map_width = server->params->width;
    int map_height = server->params->height;
    server->game.tiles[find_tile(server, x, y)].player--;

    switch (orientation) {
        case 0: // North - decrease y
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y = (y - 1 + map_height) % map_height;
            server->clients[server->id].pos_y = (y - 1 + map_height) % map_height;
            server->game.tiles[find_tile(server, x, POS_Y)].player++;
            break;
        case 1: // East - increase x
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x = (x + 1) % map_width;
            server->clients[server->id].pos_x = (x + 1) % map_width;
            server->game.tiles[find_tile(server, POS_X, y)].player++;
            break;
        case 2: // South - increase y
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y = (y + 1) % map_height;
            server->clients[server->id].pos_y = (y + 1) % map_height;
            server->game.tiles[find_tile(server, x, POS_Y)].player++;
            break;
        case 3: // West - decrease x
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x = (x - 1 + map_width) % map_width;
            server->clients[server->id].pos_x = (x - 1 + map_width) % map_width;
            server->game.tiles[find_tile(server, POS_X, y)].player++;
            break;
    }
}

void send_forward(t_server *server)
{
    modify_position(server);
    send_to_client(server, "ok\n", server->id);
}

void send_forward_to_all(t_server *server)
{
    modify_position(server);
    send_to_all_clients(server, "ok\n");
}

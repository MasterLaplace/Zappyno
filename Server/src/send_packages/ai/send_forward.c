/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_forward.c
*/

#include "../../../include/send_package.h"

enum Direction { North = 1, East, South, West };

static void modify_position(t_server *server, int id)
{
    t_client *player = &TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM];
    unsigned x = player->pos_x, y = player->pos_y, new_x = x, new_y = y;
    TILES(find_tile(server, x, y, id)).player--;
    switch (player->orientation) {
        case North:
            new_y = (y - 1 + server->params->height) % server->params->height;
            break;
        case East:
            new_x = (x + 1) % server->params->width;
            break;
        case South:
            new_y = (y + 1) % server->params->height;
            break;
        case West:
            new_x = (x - 1 + server->params->width) % server->params->width;
            break;
    }
    player->pos_x = CLIENT(id).pos_x = new_x;
    player->pos_y = CLIENT(id).pos_y = new_y;
    TILES(find_tile(server, new_x, new_y, id)).player++;
}

void send_forward(t_server *server, int id)
{
    modify_position(server, id);
    printf("Position player : %d %d\n", CLIENT(id).pos_x,
        CLIENT(id).pos_y);
    send_to_client(server, "ok\n", id);
}

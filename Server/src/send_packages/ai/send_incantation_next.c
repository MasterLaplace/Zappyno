/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_incantation_next.c
*/

#include "../../../include/send_package.h"

void freeze_participating_players_next(t_server *server, t_client* player,
int j)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    int x = player->pos_x;
    int y = player->pos_y;

    for (int i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            TEAMS[j].players[i].is_freezed = true;
        }
    }
}

void freeze_participating_players(t_server *server, t_client* player)
{
    for (int j = 0; j < server->params->num_teams; j++) {
        freeze_participating_players_next(server, player, j);
    }
}

void perform_elevation_next(t_server *server, int j, int level,
t_client* player)
{
    int x = player->pos_x;
    int y = player->pos_y;
    for (int i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            TEAMS[j].players[i].level++;
            TEAMS[j].players[i].is_freezed = false;
        }
    }
}

void send_perform_elevation(t_server *server, int j, int level,
t_client* player)
{
    int x = player->pos_x;
    int y = player->pos_y;
    for (int i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            send_to_client(server, "Current level: ++", TEAMS[j].players[i].id);
        }
    }
}

void perform_elevation(t_server *server)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    t_client* player = &CLIENT(server->id);
    for (int j = 0; j < server->params->num_teams; j++) {
        perform_elevation_next(server, j, level, player);
    }
    for (int j = 0; j < server->params->num_teams; j++) {
        send_perform_elevation(server, j, level, player);
    }
}

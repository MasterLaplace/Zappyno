/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_incantation_next.c
*/

#include "../../../include/send_package.h"

static bool freeze_participating_players_next(t_server *server,
    t_client* player, unsigned j, int id)
{
    unsigned level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    unsigned x = player->pos_x;
    unsigned y = player->pos_y;
    int *players = calloc(TEAMS[j].max_players, sizeof(int));
    if (!players)
        return false;
    unsigned index = 0;

    for (unsigned i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            TEAMS[j].players[i].is_freezed = true;
            players[index] = TEAMS[j].players[i].id;
        }
    }
    players[index] = -1;
    tmp_t tmp = {CLIENT(id).pos_x, CLIENT(id).pos_y};
    send_start_of_an_incantation(server, tmp, (level + 1), players);
    return true;
}

bool freeze_participating_players(t_server *server, t_client* player, int id)
{
    for (unsigned j = 0; j < server->params->num_teams; j++) {
        if (!freeze_participating_players_next(server, player, j, id))
            return false;
    }
    return true;
}

void perform_elevation_next(t_server *server, unsigned j, unsigned level,
    t_client* player)
{
    unsigned x = player->pos_x;
    unsigned y = player->pos_y;

    for (unsigned i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
                TEAMS[j].players[i].pos_y == y &&
                (level + 1) == TEAMS[j].players[i].level) {
            TEAMS[j].players[i].level++;
            TEAMS[j].players[i].is_freezed = false;
        }
    }
}

void perform_elevation(t_server *server, int id)
{
    unsigned level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    t_client* player = &CLIENT(id);

    for (unsigned j = 0; j < server->params->num_teams; j++) {
        perform_elevation_next(server, j, level, player);
        CLIENT(id).level++;
        TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level++;
    }
}

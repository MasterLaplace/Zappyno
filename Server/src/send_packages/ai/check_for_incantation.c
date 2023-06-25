/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** check_for_incantation.c
*/

#include "../../../include/send_package.h"

static int required_ressources[8][8] = {
        //level | nb of player| linen| dera| sibu| mend| phir| thys
        {1, 1, 1, 0, 0, 0, 0, 0},  // for level 1
        {2, 2, 1, 1, 1, 0, 0, 0},  // for level 2
        {3, 2, 2, 0, 1, 0, 2, 0},  // for level 3
        {4, 4, 1, 1, 2, 0, 1, 0},  // for level 4
        {5, 4, 1, 2, 1, 3, 0, 0},  // for level 5
        {6, 6, 1, 2, 3, 0, 1, 0},  // for level 6
        {7, 6, 2, 2, 2, 2, 2, 1}   // for level 7
};

void remove_player_resources(t_server *server, t_client *player, int pos,
int level)
{
    if (player->pos_x != CLIENT(server->id).pos_x ||
        player->pos_y != CLIENT(server->id).pos_y ||
        (level + 1) != player->level) {
        return;
    }
    for (int k = 1; k < TOTAL_RESOURCES; k++) {
        if (TILES(pos).resources[k] >= required_ressources[level][k + 1]) {
            TILES(pos).resources[k] -= required_ressources[level][k + 1];
        }
    }
}

void remove_required_resources(t_server *server)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    int pos = find_tile(server, CLIENT(server->id).pos_x,
                        CLIENT(server->id).pos_y);
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < TEAMS[j].max_players; i++) {
            remove_player_resources(server, &TEAMS[j].players[i], pos, level);
        }
    }
}
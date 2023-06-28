/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** check_for_incantation.c
*/

#include "../../../include/send_package.h"

static unsigned required_ressources[8][8] = {
    //level | nb of player| linen| dera| sibu| mend| phir| thys
    {1, 1, 1, 0, 0, 0, 0, 0},  // for level 1
    {2, 2, 1, 1, 1, 0, 0, 0},  // for level 2
    {3, 2, 2, 0, 1, 0, 2, 0},  // for level 3
    {4, 4, 1, 1, 2, 0, 1, 0},  // for level 4
    {5, 4, 1, 2, 1, 3, 0, 0},  // for level 5
    {6, 6, 1, 2, 3, 0, 1, 0},  // for level 6
    {7, 6, 2, 2, 2, 2, 2, 1}   // for level 7
};

static void remove_player_resources(t_server *server, t_client *player,
    unsigned level, int id)
{
    unsigned pos = find_tile(server, CLIENT(id).pos_x, CLIENT(id).pos_y);

    if (player->pos_x != CLIENT(id).pos_x ||
        player->pos_y != CLIENT(id).pos_y ||
        (level + 1) != player->level) {
        return;
    }
    for (unsigned k = 1; k < TOTAL_RESOURCES; k++) {
        if (TILES(pos).resources[k] >= required_ressources[level][k + 1])
            TILES(pos).resources[k] -= required_ressources[level][k + 1];
    }
}

void remove_required_resources(t_server *server, int id)
{
    unsigned level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;

    for (unsigned j = 0; j < server->params->num_teams; j++) {
        for (unsigned i = 0; i < TEAMS[j].max_players; i++)
            remove_player_resources(server, &TEAMS[j].players[i], level, id);
    }
}

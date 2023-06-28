/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_incantation.c
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

unsigned verify_elevation_conditions_next(t_server *server, unsigned j, int id)
{
    unsigned nb_players = 0;
    unsigned x = CLIENT(id).pos_x;
    unsigned y = CLIENT(id).pos_y;
    unsigned level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;

    for (unsigned i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            nb_players++;
        }
    }
    return nb_players;
}

bool verify_nmb_ressources_next(t_server *server, tmp_t tmp, unsigned level, int id)
{
    int i = tmp.i, j = tmp.j;
    unsigned x = CLIENT(id).pos_x;
    unsigned y = CLIENT(id).pos_y;
    unsigned pos = find_tile(server, x, y);
    bool check = false;
    if (TEAMS[j].players[i].pos_x == x ||
        TEAMS[j].players[i].pos_y == y ||
        (level + 1) == TEAMS[j].players[i].level) {
        check = true;
    }
    for (unsigned k = 1; k < TOTAL_RESOURCES; k++) {
        if (TILES(pos).resources[k] < required_ressources[level][k + 1] && check)
            return false;
    }
    return true;
}

bool verify_nmb_ressources(t_server *server, unsigned j, unsigned level, int id)
{
    tmp_t tmp = {0, 0};

    for (unsigned i = 0; i < TEAMS[j].max_players; i++) {
        tmp.i = i;
        tmp.j = j;
        if (!verify_nmb_ressources_next(server, tmp, level, id))
            return false;
    }
    return true;
}

bool verify_elevation_conditions(t_server *server, int id)
{
    unsigned level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    unsigned nb_players = 0;

    for (unsigned j = 0; j < server->params->num_teams; j++)
        nb_players += verify_elevation_conditions_next(server, j, id);
    if (nb_players < required_ressources[level][1])
        return false;
    for (unsigned j = 0; j < server->params->num_teams; j++) {
        if (!verify_nmb_ressources(server, j, level, id))
            return false;
    }
    return true;
}

void send_incantation(t_server *server, int id)
{
    send_to_client(server, "Elevation underway\n", id);
    t_client* player = &CLIENT(id);
    unsigned x = player->pos_x;
    unsigned y = player->pos_y;
    tmp_t tmp = {x, y};

    if (!verify_elevation_conditions(server, id))
        return send_to_client(server, "ko\n", id);
    if (!freeze_participating_players(server, player, id))
        return send_to_client(server, "ko\n", id);
    perform_elevation(server, id);
    remove_required_resources(server, id);
    send_end_of_an_incantation(server, tmp, player->level, id);
    AUTO_FREE char *str = malloc(sizeof(char) * my_nblen(player->level) + 17);
    sprintf(str, "Current level: %d\n", player->level);
    send_to_client(server, str, id);
}

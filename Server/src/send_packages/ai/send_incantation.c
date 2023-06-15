/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_incantation.c
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

int verify_elevation_conditions_next(t_server *server, int j)
{
    int nb_players = 0;
    int x = CLIENT(server->id).pos_x;
    int y = CLIENT(server->id).pos_y;
    int pos = find_tile(server, x, y);
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;

    for (int i = 0; i < TEAMS[j].max_players; i++) {
        if (TEAMS[j].players[i].pos_x == x &&
            TEAMS[j].players[i].pos_y == y &&
            (level + 1) == TEAMS[j].players[i].level) {
            nb_players++;
        }
    }
    return nb_players;
}

bool verify_nmb_ressources_next(t_server *server, int j, int i, int level)
{
    int x = CLIENT(server->id).pos_x;
    int y = CLIENT(server->id).pos_y;
    int pos = find_tile(server, x, y);
    if (TEAMS[j].players[i].pos_x != x ||
        TEAMS[j].players[i].pos_y != y ||
        (level + 1) != TEAMS[j].players[i].level) {
        return false;
    }
    for (int k = 1; k < TOTAL_RESOURCES; k++) {
        if (TILES(pos).resources[k] < required_ressources[level][k + 1]) {
            return false;
        }
    }
    return true;
}

bool verify_nmb_ressources(t_server *server, int j, int level)
{
    for (int i = 0; i < TEAMS[j].max_players; i++) {
        if (!verify_nmb_ressources_next(server, j, i, level))
            return false;
    }
    return true;
}

bool verify_elevation_conditions(t_server *server)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    int nb_players = 0;
    int x = CLIENT(server->id).pos_x;
    int y = CLIENT(server->id).pos_y;
    int pos = find_tile(server, x, y);
    for (int j = 0; j < server->params->num_teams; j++) {
        nb_players += verify_elevation_conditions_next(server, j);
    }
    printf("nb_player: %d | required: %d\n", nb_players,
required_ressources[level][1]);
    if (nb_players < required_ressources[level][1])
        return !printf("nb_players: %d\n", nb_players);
    for (int j = 0; j < server->params->num_teams; j++) {
        if (!verify_nmb_ressources(server, j, level))
            return false;
    }
    return true;
}

void send_incantation(t_server *server)
{
    printf("incantation\n");
    t_client* player = &CLIENT(server->id);
    int x = player->pos_x;
    int y = player->pos_y;
    if (!verify_elevation_conditions(server)) {
        send_to_client(server, "ko\n", server->id);
        return;
    }
    freeze_participating_players(server, player);
    perform_elevation(server);
    remove_required_resources(server);
}

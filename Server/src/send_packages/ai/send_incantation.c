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

int verify_elevation_conditions_next(t_server *server, int j, int id)
{
    int nb_players = 0;
    int x = CLIENT(id).pos_x;
    int y = CLIENT(id).pos_y;
    int pos = find_tile(server, x, y, id);
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

bool verify_nmb_ressources_next(t_server *server, tmp_t tmp, int level, int id)
{
    int i = tmp.i, j = tmp.j;
    int x = CLIENT(id).pos_x;
    int y = CLIENT(id).pos_y;
    int pos = find_tile(server, x, y, id);
    bool check = false;
    printf("%d | %d | %d | %d | %d | %d\n", TEAMS[j].players[i].pos_x, x,
           TEAMS[j].players[i].pos_y, y, (level + 1), TEAMS[j].players[i].level);
    if (TEAMS[j].players[i].pos_x == x ||
        TEAMS[j].players[i].pos_y == y ||
        (level + 1) == TEAMS[j].players[i].level) {
        check = true;
    }
    printf("level: %d\n", level);
    for (int k = 1; k < TOTAL_RESOURCES; k++) {
        if (TILES(pos).resources[k] < required_ressources[level][k + 1] && check) {
            printf("%d\n", k);
            return false;
        }
    }
    printf("GOOD\n");
    return true;
}

bool verify_nmb_ressources(t_server *server, int j, int level, int id)
{
    tmp_t tmp = {0, 0};
    for (int i = 0; i < TEAMS[j].max_players; i++) {
        tmp.i = i;
        tmp.j = j;
        if (!verify_nmb_ressources_next(server, tmp, level, id)) {
            printf("TMPPPPP\n");
            return false;
        }
    }
    printf("GOOD\n");
    return true;
}

bool verify_elevation_conditions(t_server *server, int id)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level - 1;
    int nb_players = 0;
    for (int j = 0; j < server->params->num_teams; j++) {
        nb_players += verify_elevation_conditions_next(server, j, id);
    }
    printf("nb_player: %d | required: %d\n", nb_players,
required_ressources[level][1]);
    if (nb_players < required_ressources[level][1])
        return !printf("nb_players: %d\n", nb_players);
    printf("incantation4564684\n");
    for (int j = 0; j < server->params->num_teams; j++) {
        bool test = verify_nmb_ressources(server, j, level, id);
        printf("test: %d\n", test);
        if (!test) {
            printf("WOOOOW\n");
            return false;
        }
        printf("incantation/////\n");
    }
    return true;
}

void send_incantation(t_server *server, int id)
{
    send_to_client(server, "Elevation underway\n", id);
    printf("incantation\n");
    t_client* player = &CLIENT(id);
    int x = player->pos_x;
    int y = player->pos_y;
    tmp_t tmp = {x, y};
    if (!verify_elevation_conditions(server, id)) {
        send_to_client(server, "ko\n", id);
        return;
    }
    printf("incantation50\n");
    if (!freeze_participating_players(server, player, id)) {
        printf("incantation1.0\n");
        send_to_client(server, "ko\n", id);
        return;
    }
    printf("incantation2.0\n");
    perform_elevation(server, id);
    remove_required_resources(server, id);
    send_end_of_an_incantation(server, tmp, player->level, id);
    AUTO_FREE char *str = malloc(sizeof(char) * my_nblen(player->level) + 17);
    sprintf(str, "Current level: %d\n", player->level + 1);
    send_to_client(server, str, id);
}

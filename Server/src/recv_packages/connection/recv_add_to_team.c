/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void init_inventory(int *resources)
{
    resources[FOOD] = 10;
    resources[LINEMATE] = 0;
    resources[DERAUMERE] = 0;
    resources[SIBUR] = 0;
    resources[MENDIANE] = 0;
    resources[PHIRAS] = 0;
    resources[THYSTAME] = 0;
}

/**
 * adds a player to a team with the required informations
 * @param server
 * @param message
 * @param i
 */
static void add_to_team(t_server *server, int i)
{
    TEAMS[i].nb_players++;
    for (int j = 0; j < TEAMS[i].max_players; j++) {
        if (TEAMS[i].players[j].socket_fd == 0) {
            TEAMS[i].players[j].socket_fd = CLIENT(server->id).socket_fd;
            CLIENT(server->id).pos_x = TEAMS[i].players[j].pos_x;
            CLIENT(server->id).pos_y = TEAMS[i].players[j].pos_y;
            CLIENT(server->id).is_connected = true;
            CLIENT(server->id).is_gui = false;
            TEAMS[i].players[j].orientation = rand() % 4;
            TEAMS[i].players[j].is_an_egg = false;
            TEAMS[i].players[j].level = 1;
            CLIENT(server->id).index_team = i;
            CLIENT(server->id).index_in_team = j;
            TEAMS[i].players[j].id = server->id;
            init_inventory(TEAMS[i].players[j].resources);
            TILES(find_tile(server, TEAMS[i].players[j].pos_x,
TEAMS[i].players[j].pos_y)).player++;
            break;
        }
    }
}

/**
 * Add client to specified team
 * @param server
 * @param params
 * @param game
 * @param team_name
 */
bool recv_check_to_add_to_team(t_server *server, char **message)
{
    printf("An AI is trying to join the team : \"%s\"\n", message[0]);
    for (int i = 0; i < server->params->num_teams; i++) {
        if (strcmp(message[0], server->params->team_names[i]))
            continue;
        if (TEAMS[i].nb_players >= TEAMS[i].max_players)
            return send_error(server, 0), false;
        add_to_team(server, i);
        send_join_ai(server);
        return true;
    }
    send_error(server, 1);
    return false;
}

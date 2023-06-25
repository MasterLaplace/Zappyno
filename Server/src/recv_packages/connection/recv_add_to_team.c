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

static void add_team_next(t_server *server, int i, int j, int id)
{
    CLIENT(id).orientation = TEAMS[i].players[j].orientation;
    TEAMS[i].players[j].is_an_egg = false;
    TEAMS[i].players[j].level = 1;
    CLIENT(id).index_team = i;
    CLIENT(id).index_in_team = j;
    TEAMS[i].players[j].id = id;
    init_inventory(TEAMS[i].players[j].resources);
    TILES(find_tile(server, TEAMS[i].players[j].pos_x,
                    TEAMS[i].players[j].pos_y, id)).player++;
    printf("id = %d\n", id);
    if (TEAMS[i].players[j].is_forked) {
        send_player_connection_for_an_egg(server, id);
    } else {
        send_con_of_new_player(server, &TEAMS[i].players[j], id);
    }
}

/**
 * adds a player to a team with the required informations
 * @param server
 * @param message
 * @param i
 */
static void add_to_team(t_server *server, int i, int id)
{
    TEAMS[i].nb_players++;
    for (int j = 0; j < TEAMS[i].max_players; j++) {
        if (TEAMS[i].players[j].socket_fd == 0 && id == -1) {
            printf("id = %d\n", id);
            CLIENT(id).id = id;
        }
        if (TEAMS[i].players[j].socket_fd == 0) {
            TEAMS[i].players[j].socket_fd = CLIENT(id).socket_fd;
            CLIENT(id).pos_x = TEAMS[i].players[j].pos_x;
            CLIENT(id).pos_y = TEAMS[i].players[j].pos_y;
            CLIENT(id).is_connected = true;
            CLIENT(id).is_gui = false;
            TEAMS[i].players[j].orientation = (rand() % 4) + 1;
            add_team_next(server, i, j, id);
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
bool recv_check_to_add_to_team(t_server *server, char **message, int id)
{
    printf("An AI is trying to join the team : \"%s\"\n", message[0]);
    for (int i = 0; i < server->params->num_teams; i++) {
        if (strcmp(message[0], server->params->team_names[i]))
            continue;
        printf("nb_players = %d | max_players = %d\n", TEAMS[i].nb_players,
TEAMS[i].max_players);
        if (TEAMS[i].nb_players >= TEAMS[i].max_players)
            return send_error(server, 0, id), false;
        add_to_team(server, i, id);
        send_join_ai(server, id);
        return true;
    }
    send_error(server, 0, id);
    return false;
}

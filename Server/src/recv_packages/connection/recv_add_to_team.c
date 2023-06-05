/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void init_inventory(int* resources) {
    resources[FOOD] = 10;
    resources[LINEMATE] = 1;
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
    server->game.teams[i].nb_players++;
    for (int j = 0; j < server->game.teams[i].max_players; j++) {
        if (server->game.teams[i].players[j].socket_fd == 0) {
            server->game.teams[i].players[j].socket_fd = server->clients[server->id].socket_fd;
            printf("pos x : %d | pos y : %d | j = %d\n", server->game.teams[i].players[j].pos_x,
                   server->game.teams[i].players[j].pos_y, j);
            server->clients[server->id].pos_x = server->game.teams[i].players[j].pos_x;
            server->clients[server->id].pos_y = server->game.teams[i].players[j].pos_y;
            server->clients[server->id].is_connected = true;
            server->clients[server->id].is_gui = false;
            server->game.teams[i].players[j].orientation = rand() % 4;
            server->game.teams[i].players[j].is_an_egg = false;
            server->game.teams[i].players[j].level = 1;
            server->clients[server->id].index_team = i;
            server->clients[server->id].index_in_team = j;
            server->game.teams[i].players[j].id = server->id;
            init_inventory(server->game.teams[i].players[j].resources);
            server->game.tiles[find_tile(server, server->game.teams[i].players[j].pos_x,
                server->game.teams[i].players[j].pos_y)].player++;
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
        printf("%s | %s\n", message[0], server->params->team_names[i]);
        if (!strcmp(message[0], server->params->team_names[i])) {
            if (server->game.teams[i].nb_players >= server->game.teams[i].max_players) {
                send_error(server, 0);
                return false;
            }
            printf("ok2\n");
            add_to_team(server, i);
            printf("ok\n");
            send_join_ai(server);
            return true;
        }
    }
    send_error(server, 0);
    return false;
}


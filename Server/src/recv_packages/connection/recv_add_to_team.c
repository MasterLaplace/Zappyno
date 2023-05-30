/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

static void add_to_team(t_server *server, JoinAI *join)
{
    for (int i = 0; i < server->params->num_teams; i++) {
        if (!strcmp(join->team_name, server->params->team_names[i]) && server->game.teams[i].nb_players < server->params->clientsNb) {
            server->game.teams[i].nb_players++;
            for (int j = 0; j < server->params->clientsNb; j++) {
                if (server->game.teams[i].players[j].socket_fd == 0) {
                    server->game.teams[i].players[j] = server->clients[server->id];
                    break;
                }
            }
            server->clients[server->id].is_connected = true;
            server->clients[server->id].is_gui = false;
            server->index_team = i;
            send_join_ai_to_all(server);
            return;
        } else {
            if (server->game.teams[i].nb_players >= server->params->clientsNb) {
                printf("Team is full\n");
                send_error_to_all(&server->clients[server->id], 1);
                remove_client(server, server->id);
                return;
            } else {
                printf("Team name not found\n");
                send_error_to_all(&server->clients[server->id], 2);
                remove_client(server, server->id);
                return;
            }
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
void recv_check_to_add_to_team(t_server *server, u_int8_t *buffer)
{
    JoinAI *join = (JoinAI *) &buffer[sizeof(Package_t)];
    if (!join->team_name) {
        send_error(&server->clients[server->id], 8);
        remove_client(server, server->id);
    } else {
        printf("An AI is trying to join the team : \"%s\"\n", join->team_name);
        add_to_team(server, join);
        printf("OKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n");
    }
}


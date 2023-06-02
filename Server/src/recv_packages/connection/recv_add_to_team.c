/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

/**
 * adds a player to a team with the required informations
 * @param server
 * @param message
 * @param i
 */
static void add_to_team(t_server *server, char **message, int i)
{
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
}

/**
 * doesn't add the client and removes it from the server
 * @param server
 * @param message
 * @param i
 */
static void remove_from_team(t_server *server, char **message, int i)
{
    if (server->game.teams[i].nb_players >= server->params->clientsNb) {
        printf("Team is full\n");
        send_error_to_all(server, 1);
        remove_client(server, server->id);
    } else {
        printf("Team name not found\n");
        send_error_to_all(server, 0);
        remove_client(server, server->id);
    }
}

/**
 * Add client to specified team
 * @param server
 * @param params
 * @param game
 * @param team_name
 */
void recv_check_to_add_to_team(t_server *server, char **message)
{
    char response[1024] = {0};
    printf("An AI is trying to join the team : \"%s\"\n", message[0]);
    for (int i = 0; i < server->params->num_teams; i++) {
        if (!strcmp(message[0], server->params->team_names[i]) &&
            server->game.teams[i].nb_players < server->params->clientsNb) {
            add_to_team(server, message, i);
            sprintf(response, "%d\n%d %d\n", (server->params->clientsNb - server->game.teams[i].nb_players), server->params->width, server->params->height);
            send_to_client(server, response);
            return;
        } else {
            remove_from_team(server, message, i);
            return;
        }
    }
}


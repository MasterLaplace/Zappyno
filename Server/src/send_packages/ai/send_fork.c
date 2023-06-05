/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_fork.c
*/

#include "../../../include/send_package.h"

void send_fork(t_server *server)
{
    server->game.teams[TEAM_INDEX].max_players += 1;
    server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].is_an_egg = true;
    server->game.teams = realloc(server->game.teams, sizeof(t_teams) * (server->game.teams[TEAM_INDEX].max_players));
    server->game.teams[server->game.teams[TEAM_INDEX].max_players - 1].players = calloc(1, sizeof(t_client));
    send_to_client(server, "ok\n", server->id);
}

void send_fork_to_all(t_server *server)
{
    char *message = calloc(9, sizeof(char));
    sprintf(message, "pfk %d\n", server->id);
    send_to_all_clients(server, message);
}
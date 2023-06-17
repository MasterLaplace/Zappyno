/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_fork.c
*/

#include "../../../include/send_package.h"

void send_fork(t_server *server)
{
    TEAMS[TEAM_INDEX].max_players += 1;
    TEAMS = realloc(TEAMS, sizeof(t_teams) * TEAMS[TEAM_INDEX].max_players);

    TEAMS[TEAM_INDEX].players = realloc(TEAMS[TEAM_INDEX].players, sizeof(t_client) * TEAMS[TEAM_INDEX].max_players);
    TEAMS[TEAM_INDEX].players[TEAMS[TEAM_INDEX].max_players - 1].is_an_egg = true;
    send_to_client(server, "ok\n", server->id);
}

void send_fork_to_all(t_server *server)
{
    char *message = calloc(9, sizeof(char));
    sprintf(message, "pfk %d\n", server->id);
    send_to_all_clients(server, message);
}

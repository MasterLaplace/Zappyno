/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_ai.c
*/

#include "../../../include/send_package.h"

void send_join_ai(t_server *server)
{
    char response[1024] = {0};
    sprintf(response, "%d\n%d %d\n", (server->game.teams[TEAM_INDEX].max_players - server->game.teams[TEAM_INDEX].nb_players), server->params->width, server->params->height);
    send_to_client(server, response, server->id);
}

void send_join_ai_to_all(t_server *server)
{
    char response[1024] = {0};
    sprintf(response, "%d\n%d %d\n", (server->game.teams[TEAM_INDEX].max_players - server->game.teams[TEAM_INDEX].nb_players), server->params->width, server->params->height);
    send_to_all_clients(server, response);
}
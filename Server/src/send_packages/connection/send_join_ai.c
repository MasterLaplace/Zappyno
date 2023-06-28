/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_ai.c
*/

#include "../../../include/send_package.h"

void send_join_ai(t_server *server, int id)
{
    char response[1024] = {0};

    sprintf(
        response, "%d\n%d %d\n",
        (TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players),
        server->params->width, server->params->height
    );
    send_to_client(server, response, id);
}

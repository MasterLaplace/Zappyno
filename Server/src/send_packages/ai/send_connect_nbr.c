/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"

void send_connect_nbr(t_server *server)
{
    printf("Connect_nbr : %d\n",
            (TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players));
    AUTO_FREE char *response = malloc(sizeof(char) * my_nblen(
(TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players)) + 2);
    if (!response)
        return;
    sprintf(response, "%d\n",
            (TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players));
    send_to_client(server, response, server->id);
}

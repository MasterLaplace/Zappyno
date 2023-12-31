/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"

void send_connect_nbr(t_server *server, int id)
{
    AUTO_FREE char *response = malloc(sizeof(char) * my_nblen(
        (TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players)
    ) + 2);
    if (!response)
        return;
    sprintf(response, "%d\n", (TEAMS[TEAM_INDEX].max_players - TEAMS[TEAM_INDEX].nb_players));
    send_to_client(server, response, id);
}

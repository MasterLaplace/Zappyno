/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_end_of_game
*/

#include "../../../include/send_package.h"

void send_end_of_game(t_server *server, char *team_name)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + strlen(team_name),
    sizeof(char));
    strncat(message, "seg ",strlen(message) + 4);
    strncat(message, team_name,strlen(message) + strlen(team_name));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_end_of_game_to_all(t_server *server, char *team_name)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id) + strlen(team_name),
    sizeof(char));
    strncat(message, "seg ",strlen(message) + 4);
    strncat(message, team_name,strlen(message) + strlen(team_name));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

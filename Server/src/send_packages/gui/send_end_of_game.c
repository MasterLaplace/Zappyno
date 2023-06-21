/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_end_of_game
*/

#include "../../../include/send_package.h"

void send_end_of_game(t_server *server, char *team_name)
{
    AUTO_FREE char *message = calloc(7 + strlen(team_name),sizeof(char));
    sprintf(message, "seg %s\n", team_name);
    send_to_gui(server, message, server->id);
}

void send_end_of_game_to_all(t_server *server, char *team_name)
{
    AUTO_FREE char *message = calloc(7 + strlen(team_name),sizeof(char));
    sprintf(message, "seg %s\n", team_name);
    send_to_all_gui(server, message);
}

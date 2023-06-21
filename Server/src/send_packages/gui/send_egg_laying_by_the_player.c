/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_egg_laying_by_the_player
*/

#include "../../../include/send_package.h"

void send_egg_laying_by_the_player(t_server *server, char** array)
{
    (void)(array);
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id), sizeof(char));
    sprintf(message, "pfk %d\n", server->id);
    send_to_gui(server, message, server->id);
}

void send_egg_laying_by_the_player_to_all(t_server *server, char **array)
{
    (void)(array);
    AUTO_FREE char *message = calloc(6 + my_nblen(server->id), sizeof(char));
    sprintf(message, "pfk %d\n", server->id);
    send_to_all_gui(server, message);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_egg_laying_by_the_player
*/

#include "../../include/send_package.h"

void send_egg_laying_by_the_player(t_server *server, char** array)
{
    (void)(array);
    char *message = calloc(5 + my_nblen(server->id), sizeof(char));
    strncat(message, "pfk ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_egg_laying_by_the_player_to_all(t_server *server, char **array)
{
    (void)(array);
    char *message = calloc(5 + my_nblen(server->id), sizeof(char));
    strncat(message, "pfk ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

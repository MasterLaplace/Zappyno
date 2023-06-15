/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** death_of_a_player
*/

#include "../../include/send_package.h"

void send_death_of_a_player(t_server *server, char** array)
{
    (void)(array);
    char *message = calloc(5 + my_nblen(server->id), sizeof(char));
    strncat(message, "pdi ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
    free(message);
}

void send_death_of_a_player_to_all(t_server *server, char **array)
{
    (void)(array);
    char *message = calloc(5 + my_nblen(server->id), sizeof(char));
    strncat(message, "pdi ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
    free(message);
}

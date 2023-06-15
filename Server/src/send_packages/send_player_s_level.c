/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_level
*/

#include "../../include/send_package.h"

void send_player_s_level(t_server *server, char** array)
{
    int id = atoi(array[1]);
    int lvl = server->game.teams->players[server->id].level;
    char *message = calloc(6 + my_nblen(lvl) + my_nblen(id), sizeof(char));

    strncat(message, "plv ",strlen(message) + 4);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(lvl), strlen(message) + my_nblen(lvl));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_player_s_level_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    int lvl = server->game.teams->players[server->id].level;
    char *message = calloc(6 + my_nblen(lvl) + my_nblen(id), sizeof(char));

    strncat(message, "plv ",strlen(message) + 4);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(lvl), strlen(message) + my_nblen(lvl));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

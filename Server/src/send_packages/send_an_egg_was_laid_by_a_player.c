/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_an_egg_was_laid_by_a_player
*/

#include "../../include/send_package.h"

void send_an_egg_was_laid_by_a_player(t_server *server, int egg_num, int x,
int y)
{
    char *message = calloc(8 + my_nblen(server->id) + my_nblen(egg_num) +
    my_nblen(x) + my_nblen(y), sizeof(char));
    strncat(message, "enw ",strlen(message) + 4);
    strncat(message, itoa(egg_num),strlen(message) + my_nblen(egg_num));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x),strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y),strlen(message) + my_nblen(y));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
    free(message);
}

void send_an_egg_was_laid_by_a_player_to_all(t_server *server, int egg_num,
int x, int y)
{
    char *message = calloc(8 + my_nblen(server->id) + my_nblen(egg_num) +
    my_nblen(x) + my_nblen(y), sizeof(char));
    strncat(message, "enw ",strlen(message) + 4);
    strncat(message, itoa(egg_num),strlen(message) + my_nblen(egg_num));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x),strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y),strlen(message) + my_nblen(y));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
    free(message);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_end_of_an_incantation
*/

#include "../../../include/send_package.h"

void send_end_of_an_incantation(t_server *server, tmp_t co, int res)
{
    AUTO_FREE char *message = calloc(9 + my_nblen(server->id) + my_nblen(co.i) +
    my_nblen(co.j) + my_nblen(res), sizeof(char));

    sprintf(message, "pie %d %d %d %d\n", server->id, co.i, co.j, res);
    send_to_all_gui(server, message);
}

void send_end_of_an_incantation_to_all(t_server *server, tmp_t co, char *res)
{
    AUTO_FREE char *message = calloc(9 + my_nblen(server->id) + my_nblen(co.i) +
    my_nblen(co.j) + strlen(res), sizeof(char));

    strncat(message, "pie ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(co.i),strlen(message) + my_nblen(co.i));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(co.j),strlen(message) + my_nblen(co.j));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, res,strlen(message) + strlen(res));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}
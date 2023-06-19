/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_ressource_dropping
*/

#include "../../../include/send_package.h"

void send_ressource_collecting(t_server *server, int id)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(server->id) + my_nblen(id),
    sizeof(char));
    strncat(message, "pdr ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_ressource_collecting_to_all(t_server *server, int id)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(server->id) + my_nblen(id),
    sizeof(char));
    strncat(message, "pdr ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(id),strlen(message) + my_nblen(id));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_broadcast
*/

#include "../../../include/send_package.h"

void send_broadcast_gui(t_server *server, char *brodacst)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(server->id) + strlen(brodacst),
    sizeof(char));
    strncat(message, "pbc ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, brodacst,strlen(message) + strlen(brodacst));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

void send_broadcast_gui_to_all(t_server *server, char *brodacst)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(server->id) + strlen(brodacst),
    sizeof(char));
    strncat(message, "pbc ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, brodacst,strlen(message) + strlen(brodacst));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_broadcast.c
*/

#include "../../../include/send_package.h"

void recv_broadcast(t_server *server, char **message)
{
    if (message[1] == NULL) {
        send_error(server, 0);
        return;
    }
    send_broadcast(server, message[1]);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_broadcast.c
*/

#include "../../../include/send_package.h"

void recv_broadcast(t_server *server, char **message, int id)
{
    printf("Broadcast\n");
    printf("mess = %s\n", message[1]);
    if (!message)
        return;
    printf("Broadcast\n");
    if (message[1] == NULL) {
        send_error(server, 0, id);
        return;
    }
    printf("Broadcast\n");
    send_broadcast(server, message[1], id);
}

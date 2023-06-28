/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_right.c
*/

#include "../../../include/send_package.h"

void recv_set(t_server *server, char **message, int id)
{
    if (!message)
        return;
    printf("[ai@recv] %s\n", message[0]);
    if (message[1] == NULL)
        return send_error(server, 0, id);
    send_set_object(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_take.c
*/

#include "../../../include/send_package.h"

void recv_take(t_server *server, char **message, int id)
{
    if (!message[1])
        return send_error(server, 0, id);
    send_take_object(server, message, id);
}

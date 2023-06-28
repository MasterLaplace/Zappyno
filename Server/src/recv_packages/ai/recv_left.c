/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_left.c
*/

#include "../../../include/send_package.h"

void recv_left(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] left\n");
    send_left(server, id);
}

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_right.c
*/

#include "../../../include/send_package.h"

void recv_right(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] right\n");
    send_right(server, id);
}

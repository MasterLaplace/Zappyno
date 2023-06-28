/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_forward.c
*/

#include "../../../include/send_package.h"

void recv_forward(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] forward\n");
    send_forward(server, id);
}

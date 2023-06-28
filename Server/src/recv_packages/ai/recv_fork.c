/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_fork.c
*/

#include "../../../include/send_package.h"

void recv_fork(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] fork\n");
    send_fork(server, id);
}

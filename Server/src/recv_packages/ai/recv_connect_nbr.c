/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_connect_nbr.c
*/

#include "../../../include/send_package.h"

void recv_connect_nbr(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] connect_nbr\n");
    send_connect_nbr(server, id);
}

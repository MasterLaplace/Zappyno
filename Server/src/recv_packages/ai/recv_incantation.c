/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_incantation.c
*/

#include "../../../include/send_package.h"

void recv_incantation(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] incantation\n");
    send_incantation(server, id);
}

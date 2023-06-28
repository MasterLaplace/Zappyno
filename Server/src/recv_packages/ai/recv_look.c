/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_look.c
*/

#include "../../../include/send_package.h"

void recv_look(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] look\n");
    send_look(server, id);
}

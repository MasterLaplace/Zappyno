/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_right.c
*/

#include "../../../include/send_package.h"

void recv_right(t_server *server, UNUSED char **message)
{
    printf("Recv right\n");
    send_right(server);
}

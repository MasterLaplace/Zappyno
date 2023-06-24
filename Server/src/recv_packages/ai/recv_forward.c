/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_forward.c
*/

#include "../../../include/send_package.h"

void recv_forward(t_server *server, UNUSED char **message)
{
    printf("Recv forward\n");
    send_forward(server);
}

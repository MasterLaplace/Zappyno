/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_left.c
*/

#include "../../../include/send_package.h"

void recv_left(t_server *server, UNUSED char **message, int id)
{
    printf("Recv left\n");
    send_left(server, id);
}

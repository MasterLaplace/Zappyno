/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_incantation.c
*/

#include "../../../include/send_package.h"

void recv_incantation(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] incantation\n");
    send_incantation(server, id);
}

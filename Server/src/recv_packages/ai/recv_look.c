/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_look.c
*/

#include "../../../include/send_package.h"

void recv_look(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] look\n");
    send_look(server, id);
}

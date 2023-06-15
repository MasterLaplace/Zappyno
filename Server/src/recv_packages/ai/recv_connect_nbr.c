/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_connect_nbr.c
*/

#include "../../../include/send_package.h"

void recv_connect_nbr(t_server *server, char **message)
{
    (void)message;
    send_connect_nbr(server);
}

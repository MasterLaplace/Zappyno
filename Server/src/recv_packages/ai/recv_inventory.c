/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_inventory.c
*/

#include "../../../include/send_package.h"

void recv_inventory(t_server *server, char **message)
{
    (void)message;
    send_inventory(server);
}
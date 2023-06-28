/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_inventory.c
*/

#include "../../../include/send_package.h"

void recv_inventory(t_server *server, UNUSED char **message, int id)
{
    printf("[ai@recv] inventory\n");
    send_inventory(server, id);
}

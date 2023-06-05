/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"

void send_dead(t_server *server)
{
    remove_client(server, server->id);
    send_to_client(server, "dead\n", server->id);
}

void send_dead_to_all(t_server *server)
{
    remove_client(server, server->id);
    send_to_all_clients(server, "dead\n");
}

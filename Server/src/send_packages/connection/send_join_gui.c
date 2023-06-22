/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_gui.c
*/

#include "../../../include/send_package.h"

void send_join_gui(t_server *server)
{
    send_to_client(server, "WELCOME\n", server->id);
}

void send_join_gui_to_all(t_server *server)
{
    send_to_all_clients(server, "WELCOME\n");
}

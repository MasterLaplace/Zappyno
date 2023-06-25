/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_gui.c
*/

#include "../../../include/send_package.h"

void send_join_gui(t_server *server, int id)
{
    send_to_client(server, "WELCOME\n", id);
}

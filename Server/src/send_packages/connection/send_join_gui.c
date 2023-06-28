/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_join_gui.c
*/

#include "../../../include/send_package.h"

void send_join_gui(t_server *server, int id)
{
    send_to_client(server, "WELCOME\n", id);
}

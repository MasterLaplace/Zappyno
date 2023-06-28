/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void recv_check_to_add_gui(t_server *server, UNUSED char **message, int id)
{
    printf("[gui@recv] A gui joined the server\n");
    CLIENT(id).is_connected = true;
    CLIENT(id).is_gui = true;
    send_to_gui(server, "WELCOME GUI\n", id);
}

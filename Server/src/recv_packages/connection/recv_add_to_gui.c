/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void recv_check_to_add_gui(t_server *server, UNUSED char **message, int id)
{
    printf("A gui joined the server\n");
    CLIENT(id).is_connected = true;
    CLIENT(id).is_gui = true;
    send_to_gui(server, "WELCOME GUI\n", id);
}

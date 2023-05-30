/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void recv_check_to_add_gui(t_server *server, u_int8_t *buffer)
{
    JoinGui *join = (JoinGui *) &buffer[sizeof(Package_t)];
    if (!join->avalaible)
        send_error(&server->clients[server->id], 4);
    else {
        printf("A gui joined the server\n");
        server->clients[server->id].is_connected = true;
        server->clients[server->id].is_gui = true;
        send_join_gui_to_all(&server->clients[server->id]);
    }
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** is_connected_player
*/

#include "../../include/server.h"

bool is_connected_player(t_server *server, int id)
{
    if (id > SOMAXCONN)
        return false;
    if (server->clients[id].is_connected && !server->clients[id].is_gui)
        return true;
    return false;
}

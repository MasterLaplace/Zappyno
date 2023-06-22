/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_connection_for_an_egg
*/

#include "../../../include/send_package.h"

void send_player_connection_for_an_egg(t_server *server)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(server->id), sizeof(char));
    sprintf(message, "ebo %d\n", server->id);
    send_to_all_gui(server, message);
}

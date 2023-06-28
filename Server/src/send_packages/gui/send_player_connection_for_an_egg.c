/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_player_connection_for_an_egg
*/

#include "../../../include/send_package.h"

void send_player_connection_for_an_egg(t_server *server, int id)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(id), sizeof(char));
    if (!message)
        return;
    sprintf(message, "ebo %d\n", id);
    send_to_all_gui(server, message);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_egg_laying_by_the_player
*/

#include "../../../include/send_package.h"

void send_egg_laying_by_the_player(t_server *server, UNUSED char **array,
int id)
{
    AUTO_FREE char *message = calloc(6 + my_nblen(id), sizeof(char));
    if (!message)
        return;
    sprintf(message, "pfk %d\n", id);
    send_to_gui(server, message, id);
}

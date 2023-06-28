/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** map_commands.c
*/

#include "../../../include/send_package.h"

void send_map_size(t_server *server, char **array UNUSED, int id)
{
    AUTO_FREE char *message = calloc(100, sizeof(char));
    if (!message)
        return;
    sprintf(message, "msz %d %d\n", server->params->width,server->params->height);
    send_to_gui(server, message, id);
}

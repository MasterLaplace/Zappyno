/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_unknown_command
*/

#include "../../../include/send_package.h"

void send_command_paramater(t_server *server, int id)
{
    AUTO_FREE char *message = calloc(5,sizeof(char));
    if (!message)
        return;
    sprintf(message, "sbp\n");
    send_to_gui(server, message, id);
}

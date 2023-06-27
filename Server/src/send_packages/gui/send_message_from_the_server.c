/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_message_from_the_server
*/

#include "../../../include/send_package.h"

void send_message_from_the_server(t_server *server, char *message_, int id)
{
    AUTO_FREE char *message = calloc(6 + strlen(message_), sizeof(char));
    if (!message)
        return;
    sprintf(message, "smg %s\n", message_);
    send_to_gui(server, message, id);
}

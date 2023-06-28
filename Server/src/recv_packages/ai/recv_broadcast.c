/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_broadcast.c
*/

#include "../../../include/send_package.h"

void recv_broadcast(t_server *server, char **message, int id)
{
    if (!message)
        return;
    // concat all the message
    AUTO_FREE char *str = calloc(1, sizeof(char));
    for (unsigned i = 1; message[i]; i++) {
        str = realloc(str, sizeof(char) * (strlen(str) + strlen(message[i]) + 2));
        strcat(str, message[i]);
        if (message[i + 1])
            strcat(str, " ");
    }
    printf("[ai@recv] Broadcast: %s\n", str);
    send_broadcast(server, str, id);
}

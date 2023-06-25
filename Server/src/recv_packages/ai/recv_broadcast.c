/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_broadcast.c
*/

#include "../../../include/send_package.h"

void recv_broadcast(t_server *server, char **message, int id)
{
    printf("Broadcast\n");
    if (!message)
        return;
    //concat all the message
    AUTO_FREE char *str = calloc(1, sizeof(char));
    for (int i = 1; message[i] != NULL; i++) {
        str = realloc(str, sizeof(char) * (strlen(str) + strlen(message[i]) + 2));
        strcat(str, message[i]);
        if (message[i + 1] != NULL)
            strcat(str, " ");
    }
    printf("Broadcast: %s\n", str);
    send_broadcast(server, str, id);
}

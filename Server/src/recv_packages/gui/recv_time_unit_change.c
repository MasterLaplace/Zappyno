/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_time_unit_change.c
*/

#include "../../../include/send_package.h"

void recv_time_unit_change(t_server *server, char **message)
{
    if (message[1] != NULL) {
        send_error(server, 0);
        return;
    }
    server->params->freq = atoi(message[1]);
    if (server->params->freq < 2 || server->params->freq > 10000) {
        send_error(server, 0);
        return;
    }
    AUTO_FREE char *str = calloc(10 + my_nblen(server->params->freq),
sizeof(char));
    if (!str)
        return;
    sprintf(str, "sst %d\n", server->params->freq);
    send_to_all_gui(server, str);
}

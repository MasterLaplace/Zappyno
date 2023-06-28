/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** recv_time_unit_change.c
*/

#include "../../../include/send_package.h"

void recv_time_unit_change(t_server *server, char **message, int id)
{
    if (!message[1])
        return send_error(server, 0, id);
    server->params->freq = atoi(message[1]);
    if (server->params->freq < 2 || server->params->freq > 10000)
        return send_error(server, 0, id);
    AUTO_FREE char *str = calloc(
        10 + my_nblen(server->params->freq), sizeof(char)
    );
    if (!str)
        return;
    sprintf(str, "sst %d\n", server->params->freq);
    send_to_all_gui(server, str);
}

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_time_unit.c
*/

#include "../../../include/send_package.h"

void send_time_unit(t_server *server, UNUSED char **message, UNUSED int id)
{
    AUTO_FREE char *time_unit = calloc(
        10 + my_nblen(server->params->freq), sizeof(char)
    );
    sprintf(time_unit, "sgt %d\n", server->params->freq);
    send_to_all_gui(server, time_unit);
}

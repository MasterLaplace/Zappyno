/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_end_of_an_incantation
*/

#include "../../../include/send_package.h"

void send_end_of_an_incantation(t_server *server, tmp_t co, int res, int id)
{
    AUTO_FREE char *message = calloc(
        9 + my_nblen(id) + my_nblen(co.i) + my_nblen(co.j) + my_nblen(res),
        sizeof(char)
    );
    if (!message)
        return;

    sprintf(message, "pie %d %d %d %d\n", id, co.i, co.j, res);
    send_to_all_gui(server, message);
}

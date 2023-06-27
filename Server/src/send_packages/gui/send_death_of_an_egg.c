/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_death_of_an_egg
*/

#include "../../../include/send_package.h"

void send_death_of_an_egg(t_server *server, int egg_num)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(egg_num), sizeof(char));
    if (!message)
        return;
    sprintf(message, "edi %d\n", egg_num);
    send_to_all_gui(server, message);
}

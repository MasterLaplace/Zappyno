/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_an_egg_was_laid_by_a_player
*/

#include "../../../include/send_package.h"

void send_an_egg_was_laid_by_a_player(t_server *server, int egg_num, int x,
    int y)
{
    AUTO_FREE char *message = calloc(
        9 + my_nblen(egg_num) + my_nblen(egg_num) + my_nblen(x) + my_nblen(y),
        sizeof(char)
    );
    if (!message)
        return;
    sprintf(message, "enw %d %d %d %d\n", egg_num, egg_num, x, y);
    send_to_all_gui(server, message);
}

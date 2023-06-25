/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_start_of_an_incantation
*/

#include "../../../include/send_package.h"

size_t count_nb_players(int *players)
{
    size_t count = 0;

    for (;players[count] != -1; count ++);
    return count;
}

bool send_start_of_an_incantation(t_server *server, tmp_t co, int l,
int *players)
{
    int size = 0;
    for (int i = 0; players[i] != -1; i++)
        size += my_nblen(players[i]);
    AUTO_FREE char *message = calloc(size + 40, sizeof(char));
    if (!message)
        return false;
    sprintf(message, "pic %d %d %d", co.i, co.j, l);
    for (int i = 0; players[i] != -1; i++) {
        char *id = calloc(my_nblen(players[i]) + 2, sizeof(char));
        sprintf(id, "%d ", players[i]);
        message = strcat(message, id);
        if (id)
            free(id);
    }
    message = strcat(message, "\n");
    send_to_all_gui(server, message);
}

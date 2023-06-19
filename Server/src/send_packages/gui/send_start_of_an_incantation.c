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

void send_start_of_an_incantation(t_server *server, tmp_t co, int l,
int *players)
{
    int size = 0;
    for (int i = 0; players[i] != -1; i++)
        size += my_nblen(players[i]);
    AUTO_FREE char *message = calloc(size + 40, sizeof(char));
    if (!message) {
        send_error(server, 0);
        return;
    }
    sprintf(message, "pic %d %d %d", co.i, co.j, l);
    for (int i = 0; players[i] != -1; i++) {
        char *id = calloc(my_nblen(players[i]) + 2, sizeof(char));
        sprintf(id, "%d ", players[i]);
        message = strcat(message, id);
        free(id);
    }
    message = strcat(message, "\n");
    send_to_all_gui(server, message);
}

void send_start_of_an_incantation_to_all(t_server *server, tmp_t co, int l,
int *players)
{
    AUTO_FREE char *message = calloc(9 + my_nblen(server->id) + my_nblen(co.i) +
    my_nblen(co.j) + my_nblen(l) + ( 2 * count_nb_players(players)),
    sizeof(char));
    strncat(message, "pic ",strlen(message) + 4);
    strncat(message, itoa(server->id),strlen(message) + my_nblen(server->id));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(co.i),strlen(message) + my_nblen(co.i));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(co.j),strlen(message) + my_nblen(co.j));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(l),strlen(message) + my_nblen(l));
    strncat(message, " ",strlen(message) + 1);
    for (int i = 0; i != count_nb_players(players); i++) {
        strncat(message, itoa(players[i]),strlen(message) +
        my_nblen(players[i]));
        strncat(message, " ",strlen(message) + 1);
    }
    sprintf(message, "%s\n", message);
    send_to_client(server, message, server->id);
}

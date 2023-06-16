/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_position
*/

#include "../../../include/send_package.h"

char *itoa(int nb)
{
    int len; //my_nblen(nb);
    int tmp = 0;
    int place = 0;
    char *nb_str = malloc(sizeof(char) * len + 1);

    if (!nb_str)
        return NULL;
    if (nb < 0) {
        nb_str[0] = '-';
        nb *= -1;
    }
    for (int i = len + place; i > place; i--) {
        tmp = nb;
        tmp %= 10;
        nb_str[i - 1] = tmp + '0';
        nb /= 10;
    }
    nb_str[len + place] = '\0';
    return nb_str;
}

void send_player_s_position(t_server *server, char** array)
{
    int x = server->game.teams->players[server->id].pos_x;
    int y = server->game.teams->players[server->id].pos_y;
    char *message = calloc(6 + strlen(itoa(x)) + strlen(itoa(y)), sizeof(char));

    strncat(message, "ppo ",strlen(message) + 4);
    strncat(message, itoa(x),strlen(message) + strlen(itoa(x)));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x),strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y),strlen(message) + my_nblen(y));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(O),strlen(message) + my_nblen(O));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, id);
    free(message);
}

void send_player_s_position_to_all(t_server *server, char **array)
{
    int id = atoi(array[1]);
    int x = server->game.teams->players[id].pos_x;
    int y = server->game.teams->players[id].pos_y;
    int O = server->game.teams->players[id].orientation;
    AUTO_FREE char *message = calloc(8 + my_nblen(x) + my_nblen(y) + my_nblen(id) +
    my_nblen(O), sizeof(char));

    strncat(message, "ppo ",strlen(message) + 4);
    strncat(message, itoa(x),strlen(message) + strlen(itoa(x)));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(x),strlen(message) + my_nblen(x));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(y),strlen(message) + my_nblen(y));
    strncat(message, " ",strlen(message) + 1);
    strncat(message, itoa(O),strlen(message) + my_nblen(O));
    sprintf(message, "%s\n", message);
    send_to_client(server, message, id);
}

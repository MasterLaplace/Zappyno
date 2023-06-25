/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"
#include <stdlib.h>
#include <math.h>

int calcul_square(int x, int y) {
    if (x == 0 && y == 0)
        return 0;
    else if (x >= 0 && y < 0 && y <= -x)
        return 8;
    else if (x > 0 && y < 0 && y > -x)
        return 1;
    else if (x > 0 && y >= 0 && y < x)
        return 2;
    else if (x > 0 && y > 0 && y >= x)
        return 3;
    else if (x <= 0 && y > 0 && y > -x)
        return 4;
    else if (x < 0 && y > 0 && y <= -x)
        return 5;
    else if (x < 0 && y <= 0 && y > x)
        return 6;
    else if (x <= 0 && y < 0 && y <= x)
        return 7;
    else
        return -1;
}

int square_orientation(t_client *receiver, int square) {
    int orientation = receiver->orientation;

    if (orientation == 2)
        square = (square + 6) % 8;
    else if (orientation == 3)
        square = (square + 4) % 8;
    else if (orientation == 4)
        square = (square + 2) % 8;

    return square;
}

int message_from(t_server *server, t_client *sender, t_client *receiver) {
    int width = server->params->width;
    int height = server->params->height;

    int dx = receiver->pos_x - sender->pos_x;
    int dy = receiver->pos_y - sender->pos_y;

    if (dx > width / 2)
        dx -= width;
    else if (dx < -width / 2)
        dx += width;

    if (dy > height / 2)
        dy -= height;
    else if (dy < -height / 2)
        dy += height;

    return calcul_square(dx, dy);
}

static void send_broadcast_message(t_server *server, char *message, tmp_t tmp, int id) {
    int i = tmp.i;
    int j = tmp.j;
    if (TEAMS[j].players[i].id == id)
        return;
    int square = message_from(server, &TEAMS[j].players[i], &TEAMS[j].players[INDEX_IN_TEAM]);
    int orientation = square_orientation(&TEAMS[j].players[INDEX_IN_TEAM], square);

    char *str = calloc(strlen(message) + 12 + my_nblen(orientation), sizeof(char));
    if (!str)
        return;
    sprintf(str, "message %d, %s\n", orientation, message);
    send_to_client(server, str, TEAMS[j].players[i].id);
    free(str);
}

void send_broadcast(t_server *server, char *message, int id)
{
    printf("broadcast: %s\n", message);
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < TEAMS[j].max_players; i++) {
            tmp_t tmp = {i, j};
            send_broadcast_message(server,message, tmp, id);
        }
    }
    send_to_client(server, "ok\n", id);
}

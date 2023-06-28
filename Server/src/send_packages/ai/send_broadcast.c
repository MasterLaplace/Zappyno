/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"
#include <stdlib.h>
#include <math.h>

int check_x(int e_x, int r_x, int map_size)
{
    int left_len = 0;
    for (int i = e_x, j = e_x; i < map_size + e_x; i++, j++) {
        if (j == map_size)
            j = 0;
        if (j == r_x) {
            left_len = i - e_x;
            break;
        }
    }
    int right_len = 0;
    for (int i = e_x, j = e_x; i > e_x - map_size; i--, j--) {
        if (j == 0)
            j = map_size - 1;
        if (j == r_x) {
            right_len = e_x - i;
            break;
        }
    }
    if (left_len == 0 && right_len != 0)
        return (right_len);
    if (ABS(left_len) < ABS(right_len) || (right_len == 0 && left_len != 0))
        return (left_len);
    return (right_len);
}

int check_y(int e_y, int r_y, int map_size)
{
    int up_len = 0;
    for (int i = e_y, j = e_y; i < map_size + e_y; i++, j++) {
        if (j == map_size)
            j = 0;
        if (j == r_y) {
            up_len = i - e_y;
            break;
        }
    }
    int down_len = 0;
    for (int i = e_y, j = e_y; i > e_y - map_size; i--, j--) {
        if (j == 0)
            j = map_size - 1;
        if (j == r_y) {
            down_len = e_y - i;
            break;
        }
    }
    if (up_len == 0 && down_len != 0)
        return (down_len);
    if (ABS(up_len) < ABS(down_len) || (down_len == 0 && up_len != 0))
        return (up_len);
    return (down_len);
}

static const int DIR[4][8] = {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 5, 6, 7, 8, 1, 2, 3, 4 },
        { 3, 4, 5, 6, 7, 8, 1, 2 },
        { 7, 8, 1, 2, 3, 4, 5, 6 },
};

int result(int orientation, double angle)
{
    if ((angle > 315 && angle < 365) || (angle > 0 && angle < 45))
        return DIR[orientation - 1][0];
    if (angle == 315)
        return DIR[orientation - 1][1];
    if (angle == 225)
        return DIR[orientation - 1][3];
    if (angle == 45)
        return DIR[orientation - 1][7];
    if (angle == 135)
        return DIR[orientation - 1][5];
    if ((angle < 225 && angle > 135))
        return DIR[orientation - 1][4];
    if ((angle < 315 && angle > 225))
        return DIR[orientation - 1][2];
    if ((angle > 135 && angle < 45))
        return DIR[orientation - 1][6];
    return (0);
}

static void send_broadcast_message(t_server *server, char *message, tmp_t tmp,
    int id)
{
    int i = tmp.i;
    int j = tmp.j;
    if (TEAMS[j].players[i].id == id)
        return;
    int square = check_x(
        TEAMS[j].players[i].pos_x, TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x,server->params->width
    );
    int square2 = check_y(
        TEAMS[j].players[i].pos_y, TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y, server->params->height
    );
    int orientation = result(
        TEAMS[j].players[i].orientation, calcul_angle(square, square2)
    );
    char *str = calloc(strlen(message) + 12 + my_nblen(orientation), sizeof(char));
    if (!str)
        return;
    sprintf(str, "message %d, %s\n", orientation, message);
    send_to_client(server, str, TEAMS[j].players[i].id);
    free(str);
}

void send_broadcast(t_server *server, char *message, int id)
{
    printf("Broadcast from %d: %s\n", id, message);
    for (unsigned j = 0; j < server->params->num_teams; j++) {
        for (unsigned i = 0; i < TEAMS[j].max_players; i++)
            send_broadcast_message(server, message, (tmp_t){i, j}, id);
    }
    send_to_client(server, "ok\n", id);
}

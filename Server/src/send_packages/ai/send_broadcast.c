/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_connect_nbr.c
*/

#include "../../../include/send_package.h"
#include <stdlib.h>

int shortest_distance(t_client *emitter, t_client *receiver, int map_width,
int map_height)
{
    printf("emitter: %d, %d\n", emitter->pos_x, emitter->pos_y);
    printf("receiver: %d, %d\n", receiver->pos_x, receiver->pos_y);
    int dx = abs(emitter->pos_x - receiver->pos_x);
    int dy = abs(emitter->pos_y - receiver->pos_y);

    dx = min(dx, map_width - dx);
    dy = min(dy, map_height - dy);

    return dx + dy;
}

static void send_broadcast_message(t_server *server, char *message,
int distance, tmp_t tmp)
{
    int i = tmp.i;
    int j = tmp.j;
    char *number = itoa(distance);
    if (!number)
        return;
    char *str = calloc(strlen(message) + 12 + strlen(number), sizeof(char));
    if (!str)
        return;
    sprintf(str, "message %d, %s\n", distance, message);
    send_to_client(server, str, TEAMS[j].players[i].id);
    if (str)
        free(str);
    if (number)
        free(number);
}

void send_broadcast(t_server *server, char *message)
{
    printf("broadcast: %s\n", message);
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < TEAMS[j].max_players; i++) {
            int distance = shortest_distance(
&TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM], &TEAMS[j].players[i],
server->params->width, server->params->height);
            tmp_t tmp = {i, j};
            send_broadcast_message(server, message, distance, tmp);
        }
    }
}

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
    int dx = abs(emitter->pos_x - receiver->pos_x);
    int dy = abs(emitter->pos_y - receiver->pos_y);

    dx = min(dx, map_width - dx);
    dy = min(dy, map_height - dy);

    return dx + dy;
}

void send_broadcast(t_server *server, char *message)
{
    char *str;
    char *number;
    for (int j = 0; j < server->params->num_teams; j++) {
        for (int i = 0; i < TEAMS[j].max_players; i++) {
            int distance = shortest_distance(
&TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM], &TEAMS[j].players[i],
server->params->width, server->params->height);
            number = itoa(distance);
            str = calloc(strlen(message) + 12 + strlen(number), sizeof(char));
            sprintf(str, "message %d, %s\n", distance, message);
            send_to_client(server, str, TEAMS[j].players[i].id);
            free(str);
            free(number);
        }
    }
}

void send_broadcast_to_all(t_server *server, char *text)
{
    unsigned x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    unsigned y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    unsigned pos = find_tile(server, x, y);

    AUTO_FREE char *message = calloc(strlen(text) + 12, sizeof(char));
    sprintf(message, "message %d, %s\n", pos, text);
    AUTO_FREE char *message2 = calloc(strlen(text) + 7, sizeof(char));
    sprintf(message2, "pbc %d %s\n", server->id, text);
    send_to_all_clients(server, message);
    send_to_all_gui(server, message2);
}

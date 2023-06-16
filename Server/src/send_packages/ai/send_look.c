/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_look.c
*/

#include "../../../include/send_package.h"

char *get_tile_resources(t_server *server, int pos, char* message)
{
    int max_size = (strlen(message) + 1) * sizeof(char);
    AUTO_FREE char *tmp = calloc(max_size, sizeof(char));
    for (int i = 0; i < TILES(pos).resources[FOOD]; i++)
        tmp = my_strcat(tmp, " food");
    for (int i = 0; i < TILES(pos).resources[LINEMATE]; i++)
        tmp = my_strcat(tmp, " linemate");
    for (int i = 0; i < TILES(pos).resources[DERAUMERE]; i++)
        tmp = my_strcat(tmp, " deraumere");
    for (int i = 0; i < TILES(pos).resources[SIBUR]; i++)
        tmp = my_strcat(tmp, " sibur");
    for (int i = 0; i < TILES(pos).resources[MENDIANE]; i++)
        tmp = my_strcat(tmp, " mendiane");
    for (int i = 0; i < TILES(pos).resources[PHIRAS]; i++)
        tmp = my_strcat(tmp, " phiras");
    for (int i = 0; i < TILES(pos).resources[THYSTAME]; i++)
        tmp = my_strcat(tmp, " thystame");
    for (int i = 0; i < TILES(pos).player; i++)
        tmp = my_strcat(tmp, " player");
    return my_strcat(message, tmp);
}

void update_position_switch(t_server *server, int *pos_tiles_seen, int *index,
tmp_t tmp)
{
    int tgx = 0, tgy = 0;
    switch (ORIENTATION) {
        case NORTH:
            tgx = wrap_x(POS_X + tmp.j - tmp.i, server->params->width);
            tgy = wrap_y(POS_Y - tmp.i, server->params->height);
            break;
        case EAST:
            tgx = wrap_x(POS_X + tmp.i, server->params->width);
            tgy = wrap_y(POS_Y + tmp.j - tmp.i, server->params->height);
            break;
        case SOUTH:
            tgx = wrap_x(POS_X - tmp.j + tmp.i, server->params->width);
            tgy = wrap_y(POS_Y + tmp.i, server->params->height);
            break;
        case WEST:
            tgx = wrap_x(POS_X - tmp.i, server->params->width);
            tgy = wrap_y(POS_Y - tmp.j + tmp.i, server->params->height);
            break;
    }
    pos_tiles_seen[*index] = find_tile(server, tgx, tgy);
}

void update_positions(t_server *server, int *pos_tiles_seen, int *index, int i)
{
    tmp_t tmp = {0};

    for (int j = 0; j < (i * 2) + 1; j++) {
        tmp.i = i;
        tmp.j = j;
        update_position_switch(server, pos_tiles_seen, index, tmp);
        (*index)++;
    }
}

void reverse_array(int *arr, int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int *get_pos_tiles_seen(t_server *server, int x, int y, int level)
{
    int *pos_tiles_seen = calloc((level * 2 + 1) * (level * 2 + 1),
sizeof(int));
    printf("pos player : %d %d\n", x, y);
    pos_tiles_seen[0] = find_tile(server, x, y);
    int index = 1;
    for (int i = 1; i <= level; i++) {
        update_positions(server, pos_tiles_seen, &index, i);
    }
    pos_tiles_seen[index] = -1;
    reverse_array(pos_tiles_seen, index); // Reverse the array before returning
    printf("SIZE array : %d\n", index);
    for (int i = 0; pos_tiles_seen[i] != -1; i++)
        printf("pos tile %d : %d\n", i, pos_tiles_seen[i]);
    return pos_tiles_seen;
}

void send_look(t_server *server)
{
    AUTO_FREE char *message = calloc(1, sizeof(char));
    int x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level;
    AUTO_FREE int *pos_tiles = get_pos_tiles_seen(server, x, y, level);
    for (int i = 0; pos_tiles[i] != -1; i++) {
        message = get_tile_resources(server, pos_tiles[i], message);
        if (pos_tiles[i + 1] != -1) {
            printf("I : %d\n", i);
            message = my_strcat(message, ",");
        }
    }
    AUTO_FREE char *tmp = calloc(strlen(message) + 4, sizeof(char));
    sprintf(tmp, "[%s]\n", &message[1]);
    send_to_client(server, tmp, server->id);
}

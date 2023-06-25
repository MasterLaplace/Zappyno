/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_look.c
*/

#include "../../../include/send_package.h"

char *get_tile_resources(t_server *server, int pos, char* message, int id)
{
    AUTO_FREE char *tmp = calloc( (strlen(message) + 1), sizeof(char));
    if (!tmp)
        return NULL;
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

void update_positions(t_server *server, int *pos_tiles_seen, int *index,
tmp_t tmp)
{
    int tgx = 0, tgy = 0, i = tmp.i, id = tmp.j;
    for (int j = 0; j < (i * 2) + 1; j++) {
        switch (ORIENTATION) {
            case NORTH:
                tgx = wrap_x(POS_X + j - i, server->params->width);
                tgy = wrap_y(POS_Y - i, server->params->height);
                break;
            case EAST:
                tgx = wrap_x(POS_X + i, server->params->width);
                tgy = wrap_y(POS_Y + j - i, server->params->height);
                break;
            case SOUTH:
                tgx = wrap_x(POS_X - j + i, server->params->width);
                tgy = wrap_y(POS_Y + i, server->params->height);
                break;
            case WEST:
                tgx = wrap_x(POS_X - i, server->params->width);
                tgy = wrap_y(POS_Y - j + i, server->params->height);
                break;
        }
        pos_tiles_seen[*index] = find_tile(server, tgx, tgy, id);
        (*index)++;
    }
}

int *get_pos_tiles_seen(t_server *server, int x, int y, int id)
{
    int level = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].level;
    int *pos_tiles_seen = calloc((level * 2 + 1) * (level * 2 + 1) + 1,
sizeof(int));
    if (!pos_tiles_seen)
        return NULL;
    pos_tiles_seen[0] = find_tile(server, x, y, id);
    int index = 1;
    for (int i = 1; i <= level; i++) {
        tmp_t tmp = {i, id};
        update_positions(server, pos_tiles_seen, &index, tmp);
    }
    pos_tiles_seen[index] = -1;
    reverse_array(pos_tiles_seen, index);
    return pos_tiles_seen;
}

void send_look(t_server *server, int id)
{
    AUTO_FREE char *message = calloc(1, sizeof(char));
    if (!message)
        return;
    int x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int orientation = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    AUTO_FREE int *pos_tiles = get_pos_tiles_seen(server, x, y, id);
    if (!pos_tiles)
        return;
    for (int i = 0; pos_tiles[i] != -1; i++) {
        message = get_tile_resources(server, pos_tiles[i], message, id);
        if (pos_tiles[i + 1] != -1)
            message = my_strcat(message, ",");
    }
    AUTO_FREE char *tmp = calloc(strlen(message) + 15, sizeof(char));
    sprintf(tmp, "[%s]\n", &message[1]);
    send_to_client(server, tmp, id);
}

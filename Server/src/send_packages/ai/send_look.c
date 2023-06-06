/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_look.c
*/

#include "../../../include/send_package.h"

char *my_strcat(char *dest, char *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    unsigned i = 0;
    unsigned e = 0;

    if (!tmp)
        return NULL;

    for (; src && src[i]; ++i)
        tmp[i] = src[i];
    for (; dest && dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    if (dest)
        free(dest);
    return tmp;
}

char *get_tile_resources(t_server *server, int pos, char* message) {
    // Calculate the maximum size required for the message
    int max_size = (strlen(message) + 15) * sizeof(char);
    char *tmp = calloc(max_size, sizeof(char));
    printf("player : %d\n", server->game.tiles[pos].player);
    for (int i = 0; i < server->game.tiles[pos].player; i++) {
        tmp = my_strcat(tmp, " player");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[FOOD]; i++) {
        tmp = my_strcat(tmp, " food");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[LINEMATE]; i++) {
        tmp = my_strcat(tmp, " linemate");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[DERAUMERE]; i++) {
        tmp = my_strcat(tmp, " deraumere");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[SIBUR]; i++) {
        tmp = my_strcat(tmp, " sibur");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[MENDIANE]; i++) {
        tmp = my_strcat(tmp, " mendiane");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[PHIRAS]; i++) {
        tmp = my_strcat(tmp, " phiras");
    }
    for (int i = 0; i < server->game.tiles[pos].resources[THYSTAME]; i++) {
        tmp = my_strcat(tmp, " thystame");
    }
    message = strdup(tmp);
    free(tmp);

    return message;
}

int *get_pos_tiles_seen(t_server *server, int x, int y, int orientation, int level)
{
    int *pos_tiles_seen = calloc((level * 2 + 1) * (level * 2 + 1), sizeof(int));
    pos_tiles_seen[0] = find_tile(server, x, y);
    int index = 1;
    if (orientation == NORTH) {
        for (int i = 1; i <= level; i++) {
            for (int j = 0; j < (i * 2) + 1; j++) {
                int target_x = wrap_x(x + j - i, server->params->width);
                int target_y = wrap_y(y - i, server->params->height);
                pos_tiles_seen[index] = find_tile(server, target_x, target_y);
                index++;
            }
        }
    } else if (orientation == EAST) {
        for (int i = 1; i <= level; i++) {
            for (int j = 0; j < (i * 2) + 1; j++) {
                int target_x = wrap_x(x + i, server->params->width);
                int target_y = wrap_y(y + j - i, server->params->height);
                pos_tiles_seen[index] = find_tile(server, target_x, target_y);
                index++;
            }
        }
    } else if (orientation == SOUTH) {
        for (int i = 1; i <= level; i++) {
            for (int j = 0; j < (i * 2) + 1; j++) {
                int target_x = wrap_x(x - j + i, server->params->width);
                int target_y = wrap_y(y + i, server->params->height);
                pos_tiles_seen[index] = find_tile(server, target_x, target_y);
                index++;
            }
        }
    } else if (orientation == WEST) {
        for (int i = 1; i <= level; i++) {
            for (int j = 0; j < (i * 2) + 1; j++) {
                int target_x = wrap_x(x - i, server->params->width);
                int target_y = wrap_y(y - j + i, server->params->height);
                pos_tiles_seen[index] = find_tile(server, target_x, target_y);
                index++;
            }
        }
    }
    pos_tiles_seen[index] = -1;
    return pos_tiles_seen;
}

void send_look(t_server *server)
{
    printf("x: %d, y: %d\n", server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x,
           server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y);
    char *message = calloc(1, sizeof(char));
    printf("TEAM_INDEX: %d, INDEX_IN_TEAM: %d\n", TEAM_INDEX, INDEX_IN_TEAM);
    int x = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int orientation = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].orientation;
    int level = server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].level;
    int *pos_tiles_seen = get_pos_tiles_seen(server, x, y, orientation, level);
    for (int i = 0; pos_tiles_seen[i] != -1; i++) {
        message = my_strcat(message, get_tile_resources(server, pos_tiles_seen[i], message));
        message = my_strcat(message, ",");
    }
    char *tmp = calloc(strlen(message) + 15, sizeof(char));
    sprintf(tmp, "[%s]%d%d\n", message, x, y);
    send_to_client(server, tmp, server->id);
    if (message)
        free(message);
}

void send_look_to_all(t_server *server)
{
    char *message = calloc(15, sizeof(char));
    sprintf(message, "look %d %d\n", server->params->width, server->params->height);
    send_to_all_clients(server, message);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_set_object.c
*/

#include "../../../include/send_package.h"

static const char *resourceNames[] = {"food",
"linemate",
"deraumere",
"sibur",
"mendiane",
"phiras",
"thystame"
};

/**
 * @brief Take an object from the map
 * @param server
 * @param object_name
 */
static bool set_object(t_server *server, int index, int id)
{
    int x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int pos = find_tile(server, x, y, id);
    int *tile_resources = TILES(pos).resources;
    int *player_resources = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources;
    for (int i = 0; i < TOTAL_RESOURCES; i++) {
        printf("i = %d | index = %d\n", i, index);
        if (i == index && player_resources[i] > 0) {
            printf("set object : %d\n", i);
            tile_resources[i]++;
            player_resources[i]--;
            return true;
        }
    }
    return false;
}

void check_set_object(t_server *server, int i, int id)
{
    AUTO_FREE char *str = calloc(my_nblen(id) + 10, sizeof(char));
    sprintf(str, "pdr %d %d\n", id, i);
    if (set_object(server, i, id)) {
        send_to_all_gui(server, str);
        send_to_client(server, "ok\n", id);
        return;
    } else {
        send_error(server, 0, id);
        return;
    }
}

void send_set_object(t_server *server, char **message, int id)
{
    printf("ressource: %s\n", message[1]);
    for (int i = 0; i < TOTAL_RESOURCES; i++) {
        if (strcmp(message[1], resourceNames[i]) == 0) {
            return check_set_object(server, i, id);
        }
    }
    send_error(server, 0, id);
}

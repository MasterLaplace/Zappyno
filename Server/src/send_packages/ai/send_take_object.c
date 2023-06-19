/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_take_object.c
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
static bool take_object(t_server *server, int index)
{
    int x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    int y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    int pos = find_tile(server, x, y);
    int *tile_resources = TILES(pos).resources;
    int *player_resources = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources;
    for (int i = 0; i < TOTAL_RESOURCES; i++) {
        printf("i = %d | index = %d\n", i, index);
        if (tile_resources[i] > 0 && i == index) {
            printf("take object : %d\n", i);
            tile_resources[i]--;
            player_resources[i]++;
            return true;
        }
    }
    return false;
}

void check_take_object(t_server *server, int i)
{
    AUTO_FREE char *str = calloc(my_nblen(server->id) + 10, sizeof(char));
    sprintf(str, "pgt %d %d\n", server->id, i);
    if (take_object(server, i)) {
        send_to_all_gui(server, str);
        send_to_client(server, "ok\n", server->id);
        return;
    } else {
        send_error(server, 0);
        return;
    }
}

void send_take_object(t_server *server, char **message)
{
    printf("ressource: %s\n", message[1]);
    for (int i = 0; i < TOTAL_RESOURCES; i++) {
        if (strcmp(message[1], resourceNames[i]) == 0) {
            return check_take_object(server, i);
        }
    }
    send_error(server, 0);
}

void send_take_object_to_all(t_server *server, char **message)
{
    if (take_object(server, 0))
        send_to_all_clients(server, "ok\n");
    else
        send_error_to_all(server, 0);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_take_object.c
*/

#include "../../../include/send_package.h"

static const char *resourceNames[] = {
    "food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras",
    "thystame"
};

/**
 * @brief Take an object from the map
 * @param server
 * @param object_name
 */
static bool take_object(t_server *server, unsigned index, int id)
{
    unsigned x = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x;
    unsigned y = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y;
    unsigned pos = find_tile(server, x, y);
    unsigned *tile_resources = TILES(pos).resources;
    unsigned *player_resources = TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources;

    for (unsigned i = 0; i < TOTAL_RESOURCES; i++) {
        if (tile_resources[i] > 0 && i == index) {
            tile_resources[i]--;
            player_resources[i]++;
            return true;
        }
    }
    return false;
}

void check_take_object(t_server *server, unsigned i, int id)
{
    AUTO_FREE char *str = calloc(my_nblen(id) + 10, sizeof(char));
    sprintf(str, "pgt %d %d\n", id, i);
    if (take_object(server, i, id)) {
        send_to_all_gui(server, str);
        send_to_client(server, "ok\n", id);
    } else
        return send_error(server, 0, id);
}

void send_take_object(t_server *server, char **message, int id)
{
    for (unsigned i = 0; i < TOTAL_RESOURCES; i++) {
        if (strcmp(message[1], resourceNames[i]) == 0)
            return check_take_object(server, i, id);
    }
    send_error(server, 0, id);
}

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_inventory.c
*/

#include "../../../include/send_package.h"


static const char *resourceNames[] = {
    "food", "linemate", "deraumere",
    "sibur", "mendiane", "phiras",
    "thystame"
};

static char *generate_next(t_server *server UNUSED, char *str, int resources[])
{
    for (int i = 6; i >= 0; i--) {
        if (i != 6)
            str = my_strcat(str, ", ");
        AUTO_FREE char *number = itoa(resources[i]);
        if (!number)
            return (NULL);
        str = my_strcat(str, number);
        str = my_strcat(str, " ");
        str = my_strcat(str, (char *)resourceNames[i]);
    }
    return my_strcat(str, "[");
}

char *generate_inventory_string(t_server *server, int id)
{
    char *str = strdup("]\n");

    if (!str)
        return (NULL);
    int resources[] = {
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[FOOD],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[LINEMATE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[DERAUMERE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[SIBUR],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[MENDIANE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[PHIRAS],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[THYSTAME]
    };
    return generate_next(server, str, resources);
}

void send_inventory(t_server *server, int id)
{
    AUTO_FREE char *str = generate_inventory_string(server, id);
    if (!str)
        return;
    send_to_client(server, str, id);
}

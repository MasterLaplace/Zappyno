/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_inventory.c
*/

#include "../../../include/send_package.h"


static const char *resourceNames[] = {"food", "linemate", "deraumere",
"sibur", "mendiane", "phiras", "thystame"};

char *generate_inventory_string(t_server *server)
{
    char *str = strdup("]\n");
    int resources[] = {
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[FOOD],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[LINEMATE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[DERAUMERE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[SIBUR],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[MENDIANE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[PHIRAS],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[THYSTAME]
    };
    for (int i = 6; i >= 0; i--) {
        if (i != 6)
            str = my_strcat(str, ", ");
        AUTO_FREE char *number = itoa(resources[i]);
        str = my_strcat(str, number);
        str = my_strcat(str, " ");
        str = my_strcat(str, resourceNames[i]);
    }
    str = my_strcat(str, "[");
    return str;
}

void send_inventory(t_server *server)
{
    printf("send_inventory\n");
    AUTO_FREE char *str = generate_inventory_string(server);
    send_to_client(server, str, server->id);
}

void send_inventory_to_all(t_server *server)
{
    AUTO_FREE char *str = generate_inventory_string(server);
    send_to_all_clients(server, str);
}

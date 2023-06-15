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
    char *str = malloc(sizeof(char) * 500);
    char *tmp = malloc(sizeof(char) * 100);
    int resources[] = {
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[FOOD],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[LINEMATE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[DERAUMERE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[SIBUR],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[MENDIANE],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[PHIRAS],
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[THYSTAME]
    };
    sprintf(str, "[");
    for (int i = 0; i < 7; i++) {
        if (i > 0)
            strcat(str, " ");
        sprintf(tmp, "%s %d", resourceNames[i], resources[i]);
        strcat(str, tmp);
    }
    free(tmp);
    return strcat(str, "]\n");
}

void send_inventory(t_server *server)
{
    printf("send_inventory\n");
    char *str = generate_inventory_string(server);
    send_to_client(server, str, server->id);
    free(str);
}

void send_inventory_to_all(t_server *server)
{
    char *str = generate_inventory_string(server);
    send_to_all_clients(server, str);
    free(str);
}

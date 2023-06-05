/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_inventory.c
*/

#include "../../../include/send_package.h"


static const char *resourceNames[] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

char *generate_inventory_string(t_server *server, int i) {
    char *str = malloc(sizeof(char) * 500);
    char *tmp = malloc(sizeof(char) * 100);
    printf("generate_inventory_string\n");
    printf("server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources->food=%d\n", server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[FOOD]);
    int resources[] = {
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[FOOD],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[LINEMATE],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[DERAUMERE],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[SIBUR],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[MENDIANE],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[PHIRAS],
            server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].resources[THYSTAME]
    };

    for (int i = 0; i < 7; i++) {
        printf("resources[%d]=%d\n", i, resources[i]);
    }

    sprintf(str, "[");

    for (int i = 0; i < 7; i++) {
        if (i > 0) {
            strcat(str, " "); // Add space between resource entries.
        }
        sprintf(tmp, "%s %d", resourceNames[i], resources[i]);
        strcat(str, tmp);
    }

    strcat(str, "]\n");

    free(tmp);

    return str;
}

void send_inventory(t_server *server)
{
    printf("send_inventory\n");
    char *str = generate_inventory_string(server, 0);
    send_to_client(server, str, server->id);
    free(str);
}

void send_inventory_to_all(t_server *server)
{
    char *str = generate_inventory_string(server, 0);
    send_to_all_clients(server, str);
    free(str);
}
/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** map_commands.c
*/

#include "../../include/game.h"

t_command g_commands[] = {
        {"msz", msz},
        {NULL, NULL}
};

void handle_client_command(t_server *server, t_game *game, char *command, char *args) {
    printf("Received command: %s\n", command);
    for (int i = 0; g_commands[i].name != NULL; i++) {
        if (!strcmp(command, g_commands[i].name)) {
            g_commands[i].function(game, args);
            return;
        }
    }
    printf("Command not found\n");
    char response[128];
    sprintf(response, "ko\n");
    send_to_all_clients(server->clients, response);
}

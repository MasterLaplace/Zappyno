/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    TOTAL_RESOURCES // This will always be the total number of resources.
} e_resources;

typedef struct s_client {
    int id;
    bool is_gui;             // Whether the client is a gui or not
    int socket_fd;           // The socket file descriptor for the client
    fd_set read_fds;          // The buffer for the read file descriptor
    bool is_freezed;         // Whether the client is freezed or not
    bool is_connected;      // Whether the client is connected or not
    bool is_an_egg;
    int pos_x;
    int pos_y;
    int level;
    int orientation;
    int index_team;
    int resources[TOTAL_RESOURCES];
    int index_in_team;
    // TODO: add more client-specific data (player info, team info, etc.)
} t_client;

void client_init(t_client *client, int socket_fd);
void client_destroy(t_client *client);
#endif //CLIENT_H

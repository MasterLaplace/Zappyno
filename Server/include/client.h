/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

#include <stdbool.h>

typedef struct s_client {
    int socket_fd;           // The socket file descriptor for the client
    char *buffer;            // Buffer for incoming data
    bool active;             // Whether the client is active or not
    // TODO: add more client-specific data (player info, team info, etc.)
    struct s_client *next;  // Add a 'next' member for linked list
} t_client;

void client_init(t_client *client, int socket_fd);
void client_destroy(t_client *client);

#endif //CLIENT_H

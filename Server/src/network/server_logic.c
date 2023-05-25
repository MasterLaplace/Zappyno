/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/server.h"

/**
 * Find a client by its file descriptor
 * @param clients
 * @param fd
 * @return
 */
static t_client *find_client_by_fd(t_client *clients, int fd) {
    t_client *current = clients;

    while (current != NULL) {
        if (current->socket_fd == fd)
            return current;
        current = current->next;
    }
    return NULL;
}

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server,t_client *client, int fd) {
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received <= 0) {
        // Handle disconnect or error...
    } else {
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);
        if (client != NULL) {
            printf("Client found\n");
            //void handle_client_command(t_server *server, t_game *game, char *command, char *args)
            handle_client_command(server, server->game, buffer, NULL);
        }
    }
}

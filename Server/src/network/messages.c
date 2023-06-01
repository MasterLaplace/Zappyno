/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/server.h"

/**
 * send_to_client will send a message to a client
 * @param client
 * @param package
 * @param structure
 * @param size
 */
void send_to_client(t_client *client, char *message)
{
    int bytes_sent = send(client->socket_fd, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

//send_to_all_clients will send a message to all clients
void send_to_all_clients(t_client *clients, char * message)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].socket_fd != 0 && FD_ISSET(clients[i].socket_fd, &clients[i].read_fds)) {
            send_to_client(&clients[i], message);
        }
    }
}

u_int8_t *receive_from_client(int fd)
{
    char *message = calloc(1024, sizeof(char));
    if (recv(fd, message, 1024, 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    return message;
}

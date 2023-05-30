/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/server.h"
#include "../../include/server_package.h"

/**
 * send_to_client will send a message to a client
 * @param client
 * @param package
 * @param structure
 * @param size
 */
void send_to_client(t_client *client, Package_t *package, void *structure, size_t size)
{
    uint8_t *buffer = calloc(size + sizeof(Package_t), sizeof(uint8_t));
    memcpy(buffer, package, sizeof(Package_t));
    memcpy(buffer + sizeof(Package_t), structure, size);
    // Send the buffer over the socket
    int bytes_sent = send(client->socket_fd, buffer, size + sizeof(Package_t), 0);
    if (bytes_sent == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
}

//send_to_all_clients will send a message to all clients
void send_to_all_clients(t_client *clients, Package_t *package, void *structure, size_t size)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].socket_fd != 0 && FD_ISSET(clients[i].socket_fd, &clients[i].read_fds)) {
            send_to_client(&clients[i], package, structure, size);
        }
    }
}

u_int8_t *receive_from_client(int fd)
{
    u_int8_t *message = calloc(1024, sizeof(u_int8_t));
    if (recv(fd, message, 1024, 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    return message;
}

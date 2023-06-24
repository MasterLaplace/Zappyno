/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/server.h"
#include <errno.h>

/**
 * send_to_client will send a message to a client
 * @param client
 * @param package
 * @param structure
 * @param size
 */
void send_to_client(t_server *server, char *message, int id)
{
    t_client *client = &CLIENT(id);
    if (client->socket_fd == 0 || client->socket_fd == -1 || client->is_gui)
        return;
    int bytes_sent = send(client->socket_fd, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("send");
        sleep(1);
        send(client->socket_fd, message, strlen(message), 0);
        return;
    }
    if (errno == EPIPE) {
        remove_client(server, id);
    }
}

//send_to_all_clients will send a message to all clients
void send_to_all_clients(t_server *server, char * message)
{
    t_client *clients = server->clients;

    for (int i = 0; i < SOMAXCONN; i++) {
        if (i == server->id)
            send_to_client(server, "ok\n", server->id);
        if (clients[i].socket_fd != 0) {
            printf("Send to client %d\n", i);
            send_to_client(server, message, i);
        }
    }
}

void send_to_gui(t_server *server, char * message, int id)
{
    t_client *client = &CLIENT(id);
    if (client->socket_fd == 0 || client->socket_fd == -1 || !client->is_gui)
        return;
    int bytes_sent = send(client->socket_fd, message, strlen(message), 0);
    if (bytes_sent == -1) {
        perror("send");
        sleep(1);
        send(client->socket_fd, message, strlen(message), 0);
        return;
    }
    if (errno == EPIPE) {
        remove_client(server, id);
    }
}

void send_to_all_gui(t_server *server, char * message)
{
    t_client *clients = server->clients;

    for (int i = 0; i < SOMAXCONN; i++) {
        if (clients[i].socket_fd != 0) {
            printf("Send to client %d\n", i);
            send_to_gui(server, message, i);
        }
    }
}

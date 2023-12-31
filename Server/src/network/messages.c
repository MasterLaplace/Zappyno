/*
** EPITECH PROJECT, 2023
** Zappyno
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
    if (send(client->socket_fd, message, strlen(message), 0) == -1) {
        perror("Send failed, retrying after 1 second");
        sleep(1);
        send(client->socket_fd, message, strlen(message), 0);
        return;
    }
    if (errno == EPIPE)
        remove_client(server, id);
}

void send_to_all_clients(t_server *server, char *message, unsigned id)
{
    t_client *clients = server->clients;

    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (clients[i].socket_fd != 0 && clients[i].socket_fd != -1 &&
                !clients[i].is_gui && i != id)
            send_to_client(server, message, i);
    }
}

void send_to_gui(t_server *server, char * message, unsigned id)
{
    t_client *client = &CLIENT(id);
    if (client->socket_fd == 0 || client->socket_fd == -1 || !client->is_gui)
        return;
    if (send(client->socket_fd, message, strlen(message), 0) == -1) {
        perror("Send failed, retrying after 1 second");
        sleep(1);
        send(client->socket_fd, message, strlen(message), 0);
        return;
    }
    if (errno == EPIPE)
        remove_client(server, id);
}

void send_to_all_gui(t_server *server, char * message)
{
    t_client *clients = server->clients;

    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (clients[i].socket_fd != 0)
            send_to_gui(server, message, i);
    }
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/server.h"

//send_to_client will send a message to a specific client
void send_to_client(t_client *client, char *message)
{
    send(client->socket_fd, message, strlen(message), 0);
}

//send_to_all_clients will send a message to all clients
void send_to_all_clients(t_client *clients, char *message)
{
    t_client *current = clients;

    while (current != NULL) {
        send_to_client(current, message);
        current = current->next;
    }
}

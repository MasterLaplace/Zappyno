/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"

t_command not_connected_client[] = {
        {JOIN_AI, recv_check_to_add_to_team},
        {JOIN_GUI, recv_check_to_add_gui},
        {0, NULL}
};

t_command connected_client[] = {
    {MAP_SIZE, recv_map_size},
    {0, NULL}
};

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server, int fd) {
    char *buffer = receive_from_client(fd);
    if (!buffer)
        return;
    char **message = stwa(buffer, " \n");
    printf("Received: %s\n", buffer);
    for (int i = 0; message[i]; i++)
        printf("message[%d] = %s\n", i, message[i]);

    for (int i = 0; not_connected_client[i].command_id > 0; i++) {
        if (!strcmp(not_connected_client[i].command_id, message[0]) &&
            !server->clients[server->id].is_connected) {
            not_connected_client[i].function(server, message);
            return;
        } else if (!strcmp(connected_client[i].command_id, message[0]) &&
                    server->clients[server->id].is_connected) {
            connected_client[i].function(server, message);
            return;
        }
    }
    send_error(&server->clients[server->id], 0);
    free(buffer);
}

/**
 * Remove a client from the server
 * @param server
 * @param id
 */
void remove_client(t_server *server, int id)
{
    close(server->clients[id].socket_fd);
    FD_CLR(server->clients[id].socket_fd, &server->readfds);
    memset(&server->clients[id], 0, sizeof(t_client));
}
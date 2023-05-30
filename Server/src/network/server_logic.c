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
    printf("ID client: %d\n", server->id);
    u_int8_t *buffer = receive_from_client(fd);
    Package_t *package = (Package_t *) buffer;

    for (int i = 0; not_connected_client[i].command_id > 0; i++) {
        if (not_connected_client[i].command_id == package->command_id &&
            !server->clients[server->id].is_connected) {
            not_connected_client[i].function(server, buffer);
            return;
        } else if (connected_client[i].command_id == package->command_id &&
                    server->clients[server->id].is_connected) {
            connected_client[i].function(server, buffer);
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
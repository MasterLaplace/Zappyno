/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"

t_command ia_client[] = {
    /*{"Forward", recv_forward},
    {"Right", recv_right},
    {"Left", recv_left},
    {"Look", recv_look},
    {"Inventory", recv_inventory},
    {"Broadcast text", recv_broadcast},
    {"Connect_nbr", recv_connect_nbr},
    {"Fork", recv_fork},
    {"Eject", recv_eject},
    {"Take object", recv_take},
    {"Set object", recv_set},
    {"Incantation", recv_incantation},*/
    {0, NULL}
};

t_command gui_client[] = {
        {MAP_SIZE, recv_map_size},
        {0, NULL}
};

//join client
void join_client(t_server *server, char **message, int i)
{
    if (!strcmp(message[0], "GRAPHIC")) {
        server->clients[server->id].is_gui = true;
        recv_check_to_add_gui(server, message);
        return;
    }
    for (int j = 0; server->params->team_names[j] != NULL; j++) {
        if (!strcmp(server->params->team_names[j], message[0])) {
            recv_check_to_add_to_team(server, message);
            return;
        }
    }
}

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server, int fd) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == fd) {
            server->id = i;
            break;
        }
    }
    printf("Handling client data : %d\n", fd);
    char *buffer = receive_from_client(fd);
    if (buffer == NULL || strlen(buffer) == 0) {
        remove_client(server, server->id);
        return;
    }
    printf("Received: |%s|\n", buffer);
    char **message = stwa(buffer, "\n\t");
    for (int i = 0; message[i]; i++)
        printf("message[%d] = %s\n", i, message[i]);
    if (!server->clients[server->id].is_connected) {
        join_client(server, message, 0);
    } else {
        if (server->clients[server->id].is_gui) {
            for (int i = 0; gui_client[i].command_id > 0; i++) {
                if (!strcmp(gui_client[i].command_id, message[0])) {
                    gui_client[i].function(server, message);
                    free(buffer);
                    return;
                }
            }
        } else {
            for (int i = 0; ia_client[i].command_id > 0; i++) {
                if (!strcmp(ia_client[i].command_id, message[0])) {
                    ia_client[i].function(server, message);
                    free(buffer);
                    return;
                }
            }
        }
    }
    send_error(server, 0);
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
    server->max_fd = server->sockfd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd > server->max_fd) {
            server->max_fd = server->clients[i].socket_fd;
        }
    }
}
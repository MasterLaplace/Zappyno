/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"

char **copy_message_args(char **message) {
    // First count how many elements in message
    int count = 0;
    while (message[count] != NULL) {
        count++;
    }

    // Allocate new array
    char **copy = malloc((count + 1) * sizeof(char *));
    if (copy == NULL) {
        // Handle error
        fprintf(stderr, "Failed to allocate memory for command arguments.\n");
        return NULL;
    }

    // Copy each string
    for (int i = 0; i < count; i++) {
        copy[i] = strdup(message[i]);
        if (copy[i] == NULL) {
            // Handle error
            fprintf(stderr, "Failed to duplicate command argument.\n");
            // Cleanup already allocated memory
            for (int j = 0; j < i; j++) {
                free(copy[j]);
            }
            free(copy);
            return NULL;
        }
    }

    // Null terminate
    copy[count] = NULL;

    return copy;
}


ai_command ia_client[] = {
    {"Look", recv_look, 7},
    {"Forward", recv_forward, 7},
    {"Right", recv_right, 7},
    {"Left", recv_left, 7},
    {"Inventory", recv_inventory, 1},
    {"Connect_nbr", recv_connect_nbr, 0},
    {"Take", recv_take, 7},
    {"Set", recv_set, 7},
    {"Broadcast", recv_broadcast, 7},
    {"Fork", recv_fork, 42},
    {"Eject", recv_eject, 7},
    {"Incantation", recv_incantation, 300},
    {NULL, NULL, 0}
};

gui_command gui_client[] = {
    {MAP_SIZE, recv_map_size},
    {0, NULL},
    {TNA, send_name_of_all_the_teams},
};

//join client
bool join_client(t_server *server, char **message, int i)
{
    if (!strcmp(message[0], "GRAPHIC")) {
        server->clients[server->id].is_gui = true;
        recv_check_to_add_gui(server, message);
        return true;
    }
    return recv_check_to_add_to_team(server, message);
}

bool check_command_ai(t_server *server, char **message)
{
    for (int i = 0; ia_client[i].command_id; i++) {
        if (!strncmp(ia_client[i].command_id, message[0],
                     strlen(ia_client[i].command_id)) && !server->clients[server->id].is_freezed) {
            printf("Command %s matched, setting cooldown...\n", ia_client[i].command_id);
            server->clients[server->id].timer_set = true;
            server->clients[server->id].command_to_execute = ia_client[i].function_ai;
            server->clients[server->id].command_args = copy_message_args(message);
            server->clients[server->id].delay = clock();
            return true;
        }
    }
    return false;
}

bool check_command_gui(t_server *server, char **message)
{
    for (int i = 0; gui_client[i].command_id > 0; i++) {
        if (!strcmp(gui_client[i].command_id, message[0])) {
            gui_client[i].function(server, message);
            return true;
        }
    }
    return false;
}
/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server, int fd) {
    bool ret = false;
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
    char **message = stwa(buffer, " \n\t");
    for (int i = 0; message[i]; i++)
        printf("message[%d] = %s\n", i, message[i]);
    if (!server->clients[server->id].is_connected) {
        if (!join_client(server, message, 0))
            free(buffer);
        return;
    } else {
        if (server->clients[server->id].is_gui) {
            ret = check_command_gui(server, message);
        } else {
            ret = check_command_ai(server, message);
        }
    }
    if (!ret)
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
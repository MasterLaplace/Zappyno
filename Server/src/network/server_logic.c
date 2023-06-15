/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"
#include <time.h>

ai_command ia_client[] = {
    {"Look", recv_look, 1},
    {"Forward", recv_forward, 1},
    {"Right", recv_right, 1},
    {"Left", recv_left, 1},
    {"Inventory", recv_inventory, 1},
    {"Connect_nbr", recv_connect_nbr, 0},
    {"Take", recv_take, 1},
    {"Set", recv_set, 1},
    {"Broadcast", recv_broadcast, 1},
    {"Fork", recv_fork, 42},
    {"Eject", recv_eject, 1},
    {"Incantation", recv_incantation, 300},
    {NULL, NULL, 0}
};

gui_command gui_client[] = {
    {"msz", recv_map_size},
    {0, NULL}
};

static bool join_client(t_server *server, char **message)
{
    if (!strcmp(message[0], "GRAPHIC")) {
        CLIENT(server->id).is_gui = true;
        recv_check_to_add_gui(server, message);
        return true;
    }
    return recv_check_to_add_to_team(server, message);
}

static bool check_command_ai(t_server *server, char **message)
{
    for (int i = 0; ia_client[i].command_id; i++) {
        if (!strncmp(ia_client[i].command_id, message[0],
            strlen(ia_client[i].command_id)) &&
            !CLIENT(server->id).is_freezed) {
            printf("Command found : %s\n", ia_client[i].command_id);
            CLIENT(server->id).function = ia_client[i].function_ai;
            CLIENT(server->id).timer->start = time(NULL);
            CLIENT(server->id).timer->duration = ia_client[i].time;
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

static void set_id_player(t_server *server, int fd)
{
    for (register int i = 0; i < MAX_CLIENTS; i++) {
        if (CLIENT(i).socket_fd == fd) {
            server->id = i;
            break;
        }
    }
}

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server, int fd)
{
    bool ret = false;
    set_id_player(server, fd);
    char *buffer = receive_from_client(fd);
    if (buffer == NULL || !*buffer)
        return;
    char **message = stwa(buffer, " \n\t");
    if (!CLIENT(server->id).is_connected) {
        if (!join_client(server, message))
            free(buffer);
        return;
    } else {
        if (!CLIENT(server->id).is_gui) {
            ret = check_command_ai(server, message);
        } else {
            ret = check_command_gui(server, message);
        }
    }
    if (!ret)
        send_error(server, 0);
    free(buffer);
}

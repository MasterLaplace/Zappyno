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
        {"Connect_nbr", recv_connect_nbr, -1},
        {"Take", recv_take, 1},
        {"Set", recv_set, 1},
        {"Broadcast", recv_broadcast, 1},
        {"Fork", recv_fork, 1},
        {"Eject", recv_eject, 1},
        {"Incantation", recv_incantation, 300},
        {NULL, NULL, 0}
};

gui_command gui_client[] = {
        {"msz", recv_map_size},
        {"ppo", send_player_s_position},
        {"plv", send_player_s_level},
        {"pin", send_player_s_inventory},
        {"tna", send_name_of_all_the_teams},
        {"bct", send_content_of_a_tile},
        {"mct", send_content_of_map},
        //{"sgt", send_time_unit_request},
        //{"sst", recv_time_unit_change},
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

char **copy_array(char **array)
{
    int size = 0;
    for (; array[size]; size++);
    char **new_array = malloc(sizeof(char *) * (size + 1));

    if (!new_array)
        return NULL;
    for (int i = 0; array[i]; i++)
        new_array[i] = strdup(array[i]);
    new_array[size] = NULL;
    return new_array;
}

static bool check_command_ai(t_server *server, char **message)
{
    for (int i = 0; ia_client[i].command_id; i++) {
        if (!strncmp(ia_client[i].command_id, message[0],
                     strlen(ia_client[i].command_id)) && !CLIENT(server->id).is_freezed) {
            CLIENT(server->id).function = NULL;
            printf("Command found : %s\n", ia_client[i].command_id);
            CLIENT(server->id).function = ia_client[i].function_ai;
            printf("ok\n");
            CLIENT(server->id).timer.start = time(NULL);
            printf("ok2\n");
            CLIENT(server->id).timer.duration = ia_client[i].time;
            if (CLIENT(server->id).params_function != NULL)
                free_double_array(&CLIENT(server->id).params_function);
            CLIENT(server->id).params_function = copy_array(message);
            printf("ok3\n");
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
    for (register int i = 0; i < SOMAXCONN; i++) {
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
bool handle_client_data(t_server *server, int fd)
{
    bool ret = false;
    set_id_player(server, fd);
    AUTO_FREE char *buffer = receive_from_client(fd);
    if (buffer == NULL || !*buffer)
        return false;
    printf("Received : %s\n", buffer);
    if (!strcmp(buffer, "exit\n")) {
        remove_client(server, server->id);
        return false;
    }
    ON_CLEANUP(free_double_array) char **message = stwa(buffer, " \n\t");
    if (!CLIENT(server->id).is_connected) {
        join_client(server, message);
        ret = true;
    } else {
        if (!CLIENT(server->id).is_gui) {
            ret = check_command_ai(server, message);
        } else {
            ret = check_command_gui(server, message);
        }
    }
    if (!ret)
        send_error(server, 0);
    return true;
}

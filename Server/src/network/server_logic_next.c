/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic_next.c
*/

#include "../../include/recv_package.h"
#include <time.h>

gui_command gui_client[] = {
{"msz", send_map_size},
{"ppo", send_player_s_position},
{"plv", send_player_s_level},
{"pin", send_player_s_inventory},
{"tna", send_name_of_all_the_teams},
{"bct", send_content_of_a_tile},
{"mct", send_content_of_map},
{"sgt", send_time_unit},
{"sst", recv_time_unit_change},
{NULL, NULL}
};

void check_command_gui(t_server *server, char **message)
{
    for (int i = 0; gui_client[i].command_id > 0; i++) {
        if (!strncmp(gui_client[i].command_id, message[0],
strlen(gui_client[i].command_id))) {
            printf("Command found : %s\n", gui_client[i].command_id);
            gui_client[i].function(server, message);
            return;
        }
    }
}

char **copy_array(char **array)
{
    int size = 0;
    for (; array[size]; size++);
    char **new_array = malloc(sizeof(char *) * (size + 1));

    if (!new_array)
        return NULL;
    for (int i = 0; array[i]; i++) {
        new_array[i] = strdup(array[i]);
        if (!new_array[i])
            return NULL;
    }
    new_array[size] = NULL;
    return new_array;
}

//TODO maybe I can remove this server->id = i;
void set_id_player(t_server *server, int fd)
{
    for (register int i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd == fd) {
            CLIENT(i).id = i;
            server->id = i;
            break;
        }
    }
}

void join_client(t_server *server, char **message)
{
    if (!strcmp(message[0], "GRAPHIC")) {
        CLIENT(server->id).is_gui = true;
        recv_check_to_add_gui(server, message);
        return;
    }
    recv_check_to_add_to_team(server, message);
}

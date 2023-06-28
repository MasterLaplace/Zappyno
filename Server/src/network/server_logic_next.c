/*
** EPITECH PROJECT, 2023
** Zappyno
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

void check_command_gui(t_server *server, char **message, int id)
{
    for (unsigned i = 0; gui_client[i].command_id; i++) {
        if (!strncmp(gui_client[i].command_id, message[0], strlen(gui_client[i].command_id)))
            return gui_client[i].function(server, message, id);
    }
}

char **copy_array(char **array)
{
    unsigned size = 0;
    for (; array[size]; size++);
    char **new_array = malloc(sizeof(char *) * (size + 1));

    if (!new_array)
        return (NULL);
    for (unsigned i = 0; array[i]; i++) {
        if (!(new_array[i] = strdup(array[i])))
            return (NULL);
    }
    new_array[size] = NULL;
    return new_array;
}

void join_client(t_server *server, char **message, int id)
{
    if (!strcmp(message[0], "GRAPHIC")) {
        CLIENT(id).is_gui = true;
        return recv_check_to_add_gui(server, message, id);
    }
    recv_check_to_add_to_team(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_level
*/

#include "../../../include/send_package.h"

char *make_lvl_message(t_server *server, int id)
{
    tmp_t pos = find_in_teams(server, id);
    int lvl = TEAMS[pos.i].players[pos.j].level;
    char *message = calloc(7 + my_nblen(lvl) + my_nblen(id), sizeof(char));
    if (!message)
        return NULL;
    sprintf(message, "plv %d %d\n", id, lvl);
    return message;
}

void send_player_s_level(t_server *server, char** array, int id)
{
    if (array[1] == NULL)
        return send_command_paramater(server, id);
    int id_par = atoi(array[1]);

    if (!is_connected_player(server, id_par))
        return send_command_paramater(server, id);
    AUTO_FREE char *message = make_lvl_message(server, id_par);
    if (!message)
        return;
    send_to_gui(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_player_s_position
*/

#include "../../../include/send_package.h"

char *make_pos_message(t_server *server, int id)
{
    tmp_t pos = find_in_teams(server, id);
    int x = TEAMS[pos.i].players[pos.j].pos_x;
    int y = TEAMS[pos.i].players[pos.j].pos_y;
    int orientation = server->clients[id].orientation;
    char *message = calloc(
        9 + my_nblen(x) + my_nblen(y) + my_nblen(id) + my_nblen(orientation),
        sizeof(char)
    );
    if (message == NULL)
        return (NULL);
    sprintf(message, "ppo %d %d %d %d\n", id, x, y, orientation);
    return message;
}

void send_player_s_position(t_server *server, char** array, int id)
{
    if (array[1] == NULL)
        return send_command_paramater(server, id);
    int id_par = atoi(array[1]);

    if (!is_connected_player(server, id_par))
        return send_command_paramater(server, id);
    AUTO_FREE char *message = make_pos_message(server, id_par);
    if (message == NULL)
        return send_command_paramater(server, id);
    send_to_gui(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** send_player_s
*/

#include "../../../include/send_package.h"

size_t count_inv_size(unsigned *resources, int x, int y, int id)
{
    size_t count = 0;

    for (unsigned i = 0; i != 7; i++)
        count += my_nblen((int)resources[i]);
    return count + my_nblen(x) + my_nblen(y) + my_nblen(id);
}

char *make_inv_message(t_server *server, int id)
{
    tmp_t pos = find_in_teams(server, id);
    int data = 0;
    int x = server->game.teams[pos.i].players[pos.j].pos_x;
    int y = server->game.teams[pos.i].players[pos.j].pos_y;
    char *message = calloc(
        16 + count_inv_size(server->clients[id].resources, x, y, id),
        sizeof(char)
    );
    char *tmp = NULL;
    if (!message)
        return (NULL);
    sprintf(message, "pin %d %d %d ", id, x, y);
    for (size_t i = 0; i < 7; i++) {
        data = server->game.teams[pos.i].players[pos.j].resources[i];
        if (!(tmp = itoa(data)))
            return (NULL);
        strncat(message, tmp, strlen(message) + my_nblen(data));
        strncat(message, " ", strlen(message) + 1);
    }
    strncat(message, "\n", strlen(message) + 1);
    return message;
}

void send_player_s_inventory(t_server *server, char** array, int id)
{
    if (array[1] == NULL)
        return send_command_paramater(server, id);
    int id_par = atoi(array[1]);
    if (!is_connected_player(server, id_par))
        return send_command_paramater(server, id);
    AUTO_FREE char *message = make_inv_message(server, id_par);
    if (!message)
        return;
    send_to_gui(server, message, id);
}

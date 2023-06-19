/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_con_of_new_player
*/

#include "../../../include/send_package.h"

void send_con_of_new_player(t_server *server, t_client *player)
{
    AUTO_FREE char *message = calloc(7 + my_nblen(player->id) +
    my_nblen(player->pos_x) + my_nblen(player->pos_y) + my_nblen(player->orientation) + my_nblen(player->level) + strlen(server->game.teams[TEAM_INDEX].name), sizeof(char));
    sprintf(message, "pnw %d %d %d %d %d %s\n", player->id, player->pos_x, player->pos_y, player->orientation, player->level, server->game.teams[TEAM_INDEX].name);
    send_to_all_gui(server, message);
}

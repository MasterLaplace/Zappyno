/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_gui.c
*/

#include "../../../include/send_package.h"

/*
 * struct PACKED JoinGui {
 *    uint8_t command_id;
 * } JoinGui;
 */

void send_join_gui(t_server *server)
{
    send_to_client(&server->clients[server->id], "WELCOME");
}

void send_join_gui_to_all(t_server *server)
{
    send_to_all_clients(server->clients, "WELCOME");
}
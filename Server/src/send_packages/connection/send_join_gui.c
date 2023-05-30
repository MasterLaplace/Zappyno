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

static JoinGui set_join_gui_struct(void) {
    JoinGui join_gui;
    join_gui.avalaible = true;
    return join_gui;
}

void send_join_gui(t_client *client) {
    Package_t package;
    JoinGui join_gui = set_join_gui_struct();
    package.command_id = JOIN_GUI;
    package.size = htons(sizeof(JoinGui));
    send_to_client(client, &package, &join_gui, sizeof(JoinGui));
}

void send_join_gui_to_all(t_client *clients) {
    Package_t package;
    JoinGui join_gui = set_join_gui_struct();
    package.command_id = JOIN_GUI;
    package.size = htons(sizeof(JoinGui));
    send_to_all_clients(clients, &package, &join_gui, sizeof(JoinGui));
}
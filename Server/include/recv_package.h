/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** recv_package.h
*/

#ifndef RECV_PACKAGE_H_
#define RECV_PACKAGE_H_

#include "server.h"
#include "recv_package.h"
#include "send_package.h"

// CONNECTION DIRECTORY
// Check if the client is a gui and adds it
void recv_check_to_add_gui(t_server *server, char **message);

// Check if the client is a AI and adds it
bool recv_check_to_add_to_team(t_server *server, char **message);

// SEND DIRECTORY
// Receive the map size from the client, and sends it back if it's not the same
void recv_map_size(t_server *server, char **message);
// Receive look command from ai and sends it back
void recv_look(t_server *server, char **message);
// Receive forward command from ai and sends it back
void recv_forward(t_server *server, char **message);
// Receive left command from ai and sends it back
void recv_left(t_server *server, char **message);
// Receive right command from ai and sends it back
void recv_right(t_server *server, char **message);
// Receive inventory command from ai and sends it back
void recv_inventory(t_server *server, char **message);
// Receive connect_nbr command from ai and sends it back
void recv_connect_nbr(t_server *server, char **message);
// Receive take object command from ai and sends it back
void recv_take(t_server *server, char **message);
// Receive set object command from ai and sends it back
void recv_set(t_server *server, char **message);
// Receive broadcast command from ai and sends it back
void recv_broadcast(t_server *server, char **message);
// Receive fork command from ai and sends it back
void recv_fork(t_server *server, char **message);
// Receive eject command from ai and sends it back
void recv_eject(t_server *server, char **message);
// Receive incantation command from ai and sends it back
void recv_incantation(t_server *server, char **command);

#endif /* !RECV_PACKAGE_H_ */
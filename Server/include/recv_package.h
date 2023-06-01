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
void recv_check_to_add_to_team(t_server *server, char **message);

// SEND DIRECTORY
// Receive the map size from the client, and sends it back if it's not the same
void recv_map_size(t_server *server, char **message);


#endif /* !RECV_PACKAGE_H_ */
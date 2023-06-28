/*
** EPITECH PROJECT, 2023
** Zappyno
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
void recv_check_to_add_gui(t_server *server, char **message, int id);

// Check if the client is a AI and adds it
bool recv_check_to_add_to_team(t_server *server, char **message, int id);

// SEND DIRECTORY
// Receive look command from ai and sends it back
void recv_look(t_server *server, char **message, int id);
// Receive forward command from ai and sends it back
void recv_forward(t_server *server, char **message, int id);
// Receive left command from ai and sends it back
void recv_left(t_server *server, char **message, int id);
// Receive right command from ai and sends it back
void recv_right(t_server *server, char **message, int id);
// Receive inventory command from ai and sends it back
void recv_inventory(t_server *server, char **message, int id);
// Receive connect_nbr command from ai and sends it back
void recv_connect_nbr(t_server *server, char **message, int id);
// Receive take object command from ai and sends it back
void recv_take(t_server *server, char **message, int id);
// Receive set object command from ai and sends it back
void recv_set(t_server *server, char **message, int id);
// Receive broadcast command from ai and sends it back
void recv_broadcast(t_server *server, char **message, int id);
// Receive fork command from ai and sends it back
void recv_fork(t_server *server, char **message, int id);
// Receive eject command from ai and sends it back
void recv_eject(t_server *server, char **message, int id);
// Receive incantation command from ai and sends it back
void recv_incantation(t_server *server, char **command, int id);

#endif /* !RECV_PACKAGE_H_ */

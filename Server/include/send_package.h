/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_map_size.c
*/

#ifndef SEND_PACKAGE_H_
#define SEND_PACKAGE_H_

#include "server.h"

// CONNECTION DIRECTORY
//------------------ \\
// Send to all the clients gui joined the clients
void send_join_gui_to_all(t_server *server);
// Send to the client gui joined the clients
void send_join_gui(t_server *server);

//------------------ \\
// Send to all the Ai she joined the clients
void send_join_ai(t_server *server);
// Send to all the clients the AI joined the clients
void send_join_ai_to_all(t_server *server);

//------------------ \\
// Send to all the clients if the team exists or not
void send_team_not_exists_to_all(t_client *clients);
// Send to the client if the team exists or not
void send_team_not_exists(t_client *client);

//------------------ \\
// Send to all the client team is full
void send_team_is_full_to_all(t_client *clients);
// Send to the client team is full
void send_team_is_full(t_client *client);

//------------------ \\
// Send to all the client join is impossible
void send_error_to_all(t_client *clients, u_int8_t error_id);
// Send to the client join is impossible
void send_error(t_client *client, u_int8_t error_id);
// CONNECTION DIRECTORY



//SEND DIRECTORY
//------------------ \\
// Send to all the clients the map size
void send_map_size_to_all(t_server *server);
// Send to the client the map size
void send_map_size(t_server *server);



//OTHERS
void send_command_not_found_to_all(t_client *clients);
void send_command_not_found(t_client *client);


#endif /* !SEND_PACKAGE_H_ */

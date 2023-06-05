/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_map_size.c
*/

#ifndef SEND_PACKAGE_H_
#define SEND_PACKAGE_H_
#define min(a,b) ((a) < (b) ? (a) : (b))

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
void send_error_to_all(t_server *server, int id_error);
// Send to the client join is impossible
void send_error(t_server *server, int id_error);
// CONNECTION DIRECTORY



//SEND DIRECTORY AI
//------------------ \\
// Send to all the clients the map size
void send_map_size_to_all(t_server *server);
// Send to the client the map size
void send_map_size(t_server *server);
//
void send_look(t_server *server);
void send_look_to_all(t_server *server);
//
void send_forward(t_server *server);
void send_forward_to_all(t_server *server);
//
void send_left(t_server *server);
void send_left_to_all(t_server *server);
//
void send_right(t_server *server);
void send_right_to_all(t_server *server);
//
void send_inventory(t_server *server);
void send_inventory_to_all(t_server *server);
//
void send_connect_nbr(t_server *server);
void send_connect_nbr_to_all(t_server *server);
//
void send_take_object(t_server *server, char **message);
void send_take_object_to_all(t_server *server, char **message);
//
void send_set_object(t_server *server, char **message);
void send_set_object_to_all(t_server *server, char **message);
//
void send_broadcast(t_server *server, char *message);
void send_broadcast_to_all(t_server *server, char *message);
//
void send_fork(t_server *server);
void send_fork_to_all(t_server *server);
//
void send_eject(t_server *server);
void send_eject_to_all(t_server *server);
//
void send_incantation(t_server *server);
//
void send_dead(t_server *server);
// Send to all clients all teams names
void send_name_of_all_the_teams_to_all(t_server *server, char** array);
// Send to the client all teams names
void send_name_of_all_the_teams(t_server *server, char** array);



//OTHERS
void send_command_not_found_to_all(t_client *clients);
void send_command_not_found(t_client *client);


#endif /* !SEND_PACKAGE_H_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_map_size.c
*/

#ifndef SEND_PACKAGE_H_
    #define SEND_PACKAGE_H_
    #define min(a,b) ((a) < (b) ? (a) : (b))
    #define ORIENTATION TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].orientation
    #define POS_X TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x
    #define POS_Y TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y

    #include "server.h"
    #include "clean_up.h"

typedef struct tmp_s {
    int i;
    int j;
} tmp_t;

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

//SEND DIRECTORY GUI
//------------------ \\
// Send to all clients all teams names
void send_name_of_all_the_teams(t_server *server, char** array);
void send_name_of_all_the_teams_to_all(t_server *server, char** array);
//
void send_player_s_position(t_server *server, char** array);
void send_player_s_position_to_all(t_server *server, char **array);
//
void send_player_s_level(t_server *server, char** array);
void send_player_s_level_to_all(t_server *server, char** array);
//
void send_player_s_inventory(t_server *server, char** array);
void send_player_s_inventory_to_all(t_server *server, char** array);
//
void send_map_size(t_server *server, char** array);
void send_map_size_to_all(t_server *server, char** array);
//
void send_expulsion(t_server *server, char** array);
void send_expulsion_to_all(t_server *server, char** array);
//
void send_egg_laying_by_the_player(t_server *server, char** array);
void send_egg_laying_by_the_player_to_all(t_server *server, char** array);
//
void send_death_of_an_egg(t_server *server, int egg_num);
void send_death_of_an_egg_to_all(t_server *server, int egg_num);
//
void send_death_of_a_player(t_server *server, char** array);
void send_death_of_a_player_to_all(t_server *server, char** array);
//
void send_broadcast_gui(t_server *server, char *brodacst);
void send_broadcast_gui_to_all(t_server *server, char *brodacst);
//
bool send_start_of_an_incantation(t_server *server, tmp_t co, int l,
int *players);
void send_start_of_an_incantation_to_all(t_server *server, tmp_t co, int l,
int *players);
//
void send_end_of_an_incantation(t_server *server, tmp_t co, int l);
void send_end_of_an_incantation_to_all(t_server *server, tmp_t co, char *res);
//
void send_ressource_dropping(t_server *server, int id);
void send_ressource_dropping_to_all(t_server *server, int id);
//
void send_ressource_collecting(t_server *server, int id);
void send_ressource_collecting_to_all(t_server *server, int id);
//
void send_an_egg_was_laid_by_a_player(t_server *server, int egg_num, int x,
int y);
void send_an_egg_was_laid_by_a_player_to_all(t_server *server, int egg_num,
int x, int y);
//
void send_player_connection_for_an_egg(t_server *server);
void send_player_connection_for_an_egg_to_all(t_server *server, int egg_num);
//
void send_end_of_game(t_server *server, char *team_name);
void send_end_of_game_to_all(t_server *server, char *team_name);
//
void send_message_from_the_server(t_server *server, char *message_);
void send_message_from_the_server_to_all(t_server *server, char *message_);
//
void send_unknown_command(t_server *server);
void send_unknown_command_to_all(t_server *server);
//
void send_command_paramater(t_server *server);
void send_command_paramater_to_all(t_server *server);
//
void send_content_of_a_tile(t_server *server, char **array);
//
void send_content_of_map(t_server *server, char **array);
//
void send_con_of_new_player(t_server *server, t_client *player);
//
void send_time_unit(t_server *server, char **message);
//
void recv_time_unit_change(t_server *server, char **message);

//OTHERS
void send_command_not_found_to_all(t_client *clients);
void send_command_not_found(t_client *client);

#endif /* !SEND_PACKAGE_H_ */

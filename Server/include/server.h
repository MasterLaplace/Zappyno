/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H
    #define UNUSED __attribute__((unused))
    #define EXIT_ERROR 84
    #define BUFFER_SIZE 1024
    #define TEAMS server->game.teams
    #define CLIENT(id) server->clients[id]
    #define TILES(id) server->game.tiles[id]
    #define TEAM_INDEX CLIENT(id).index_team
    #define INDEX_IN_TEAM CLIENT(id).index_in_team
    #define RANDINT(min, max) (rand() % (max - min + 1) + min)
    #define ERROR "Error"
    #define NORTH 1
    #define EAST 2
    #define SOUTH 3
    #define WEST 4
    #define POS_X TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x
    #define POS_Y TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y

    // Include all the libraries you need here
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>
    // Includes for server setup
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/time.h>
    #include <sys/select.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <stdint.h>
    #include <fcntl.h>
    #include <time.h>

    #include "params.h"
    #include "client.h"
    #include "game.h"
    #include "clean_up.h"

typedef struct tmp_s tmp_t;

typedef struct server_timer_s {
    clock_t start;
    double duration;
} server_timer_t;

/**
 * @brief Structure that contains the server
 *
 * @param sockfd The socket file descriptor
 * @param max_fd The max file descriptor
 * @param readfds The file descriptor set
 * @param id The id of the client
 * @param clients The clients connected to the server
 * @param params The parameters of the server
 * @param game The game structure
 */
typedef struct s_server {
    bool should_die;
    bool death;
    bool remove_food;
    int sockfd;
    int max_fd;
    fd_set readfds;
    t_client clients[SOMAXCONN];
    t_params *params;
    t_game game;
    server_timer_t gen_food_timer;
    server_timer_t remove_food_timer;
    fd_set wfd;
} t_server;

// Prototypes src/network/ | function made to setup the server
bool setup_server(t_server *server, t_params *params);
// Prototypes src/network/ | function made to handle the server
void handle_client_data(t_server *server, int fd, int id);
// remove_client will remove a client from the server
void remove_client(t_server *server, int id);
// send_to_client will send a message to a specific client
void send_to_client(t_server *, char *, int);
//
void send_to_all_clients(t_server *server, char *message, int id);
// receive_from_client will receive a message from a specific client
void receive_from_client(t_server *server, char *message, int id);
//
void send_to_all_gui(t_server *server, char * message);
//
void send_to_gui(t_server *server, char * message, int id);

//
char **stwa(char *str, const char *delim);
//
unsigned find_tile(t_server *server, unsigned x, unsigned y, int id);
//
int wrap_x(int x, int width);
//
int wrap_y(int y, int height);
//
int set_timer(void);
//
bool generate_food(t_server *server);
//
t_server *set_server_struct(t_params *params);
//
bool has_timer_expired(t_client *player);
//
bool has_timer_expired_gen_food(server_timer_t *timer, double duration);
//
void init(void) __attribute__((constructor));
//
char *my_strcat(char *dest, char *src);
//
int my_nblen(int nb);
//
char *itoa(int nb);
//
void free_server(t_server **server);
//
void free_double_array(char ***array);
//
bool freeze_participating_players(t_server *server, t_client* player, int id);
//
void perform_elevation(t_server *server, int id);
//
void remove_required_resources(t_server *server, int id);
//
bool is_connected_player(t_server *server, int id);
//
tmp_t find_in_teams(t_server *server, int id);
//
void reverse_array(int *arr, int size);
//
void check_command_gui(t_server *server, char **message, int id);
//
char **copy_array(char **array);
//
void join_client(t_server *server, char **message, int id);
//
void handle_new_connection(t_server *svr);
//
int set_fds(t_server *svr);
//
void set_environment_variable(const char *key, void *ptr);
//
uintptr_t get_environment_variable(const char *key);
//
void clean(void) __attribute__((destructor));
//
void add_client(t_server *server, int new_socket);
//
double calcul_angle(int x, int y);
//
struct timespec get_current_time();



#endif // SERVER_H

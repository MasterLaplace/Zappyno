/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H
    #define EXIT_ERROR 84
    #define MAX_CLIENTS 3 // TODO : MAXCONN
    #define BUFFER_SIZE 1024
    #define TEAMS server->game.teams
    #define CLIENT(id) server->clients[id]
    #define TILES(id) server->game.tiles[id]
    #define TEAM_INDEX CLIENT(server->id).index_team
    #define INDEX_IN_TEAM CLIENT(server->id).index_in_team
    #define RANDINT(min, max) (rand() % (max - min + 1) + min)
    #define ERROR "Error"
    #define NORTH 0
    #define EAST 1
    #define SOUTH 2
    #define WEST 3
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

    #include "params.h"
    #include "client.h"
    #include "game.h"

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
    int sockfd;
    int max_fd;
    fd_set readfds;
    int id;
    t_client clients[MAX_CLIENTS];
    t_params *params;
    t_game game;
} t_server;

// Prototypes src/network/ | function made to setup the server
int setup_server(t_server *server, t_params *params);
// Prototypes src/network/ | function made to handle the server
void handle_client_data(t_server *server, int fd);
// remove_client will remove a client from the server
void remove_client(t_server *server, int id);
// send_to_client will send a message to a specific client
void send_to_client(t_server *, char *, int);
// send_to_all_clients will send a message to all clients
void send_to_all_clients(t_server *, char *);
// receive_from_client will receive a message from a specific client
char *receive_from_client(int fd);

//
char **stwa(char *str, const char *delim);
//
unsigned find_tile(t_server *server, unsigned x, unsigned y);
//
int wrap_x(int x, int width);
//
int wrap_y(int y, int height);
//
int set_timer(void);
//
void generate_food(t_server *server);
//
t_params set_param_struct(void);
//
t_server *set_server_struct(t_params *params);
//
bool has_timer_expired(t_client *player);
//
void init(void) __attribute__((constructor));
//
char *my_strcat(char *dest, char *src);

#endif // SERVER_H

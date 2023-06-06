/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server.h
*/

#ifndef SERVER_H
    #define SERVER_H
    #define EXIT_SUCCESS 0
    #define EXIT_ERROR 84
    #define MAX_CLIENTS 65  // Maximum number of clients that can connect to the server
    #define BUFFER_SIZE 1024  // Define the buffer size constant
    #define TEAM_INDEX server->clients[server->id].index_team
    #define INDEX_IN_TEAM server->clients[server->id].index_in_team
    #define RANDINT(min, max) (rand() % (max - min + 1) + min)
    #define MAP_SIZE "msz"
    #define ERROR "Error"
    #define NORTH 0
    #define EAST 1
    #define SOUTH 2
    #define WEST 3
    #define POS_X server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_x
    #define POS_Y server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].pos_y
//Include all the libraries you need here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
//Includes for server setup
#include <sys/socket.h>
#include <netinet/in.h>

#include "params.h"
#include "client.h"
#include "game.h"

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
// Prototypes src/network/ | function made to handle the server
void remove_client(t_server *server, int id);


//
char **stwa(char *str, const char *delim);
//
int find_tile(t_server *server, int x, int y);
//
int wrap_x(int x, int width);
//
int wrap_y(int y, int height);
//
int has_timed_out();
//
int set_timer();
#endif //SERVER_H
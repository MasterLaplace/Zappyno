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
    #define JOIN_GUI "gnw"
    #define JOIN_AI "pnw"
    #define MAP_SIZE "msz"
    #define ERROR "Error"

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
    int index_team;
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
void send_to_client(t_client *client, char *);
// send_to_all_clients will send a message to all clients
void send_to_all_clients(t_client *clients, char *);
// receive_from_client will receive a message from a specific client
u_int8_t *receive_from_client(int fd);
// Prototypes src/network/ | function made to handle the server
void remove_client(t_server *server, int id);


//
char **stwa(char *str, const char *delim);
#endif //SERVER_H
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
    #define MAX_CLIENTS 3  // Maximum number of clients that can connect to the server
    #define BUFFER_SIZE 1024  // Define the buffer size constant

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

typedef struct s_game t_game; // Forward declaration

typedef struct s_server {
    int sockfd;
    int client_sockets[MAX_CLIENTS];  // List of all connected client sockets
    int max_fd;  // Maximum file descriptor number
    t_client *clients;
    t_game *game;
} t_server;

//Prototypes src/network/ | function made to setup the server
int setup_server(t_server *server, t_params *params);
//Prototypes src/network/ | function made to handle the server
void handle_client_data(t_server *server,t_client *client, int fd);
// handle_client_command will call the appropriate function
void handle_client_command(t_server *server, t_game *game, char *command, char *args);
//send_to_client will send a message to a specific client
void send_to_client(t_client *client, char *message);
//send_to_all_clients will send a message to all clients
void send_to_all_clients(t_client *clients, char *message);
#endif //SERVER_H
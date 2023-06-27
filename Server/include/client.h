/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    #include <stdbool.h>
    #include <stddef.h>
    #include <time.h>

typedef struct s_server t_server;

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    TOTAL_RESOURCES // This will always be the total number of resources.
} e_resources;

typedef struct my_timer_s {
    clock_t start;
    double duration;
} my_timer_t;

typedef struct s_client {
    int id;
    int socket_fd;           // The socket file descriptor for the client
    unsigned pos_x;
    unsigned pos_y;
    unsigned level;
    unsigned orientation;
    unsigned index_team;
    unsigned resources[TOTAL_RESOURCES];
    unsigned index_in_team;
    my_timer_t timer;
    void (*function)(t_server *, char **, int);
    char **params_function;
    char *buffer;
    bool is_gui;             // Whether the client is a gui or not
    bool is_freezed;         // Whether the client is freezed or not
    bool is_connected;      // Whether the client is connected or not
    bool is_an_egg;
    bool is_forked;
    bool dead;
    // TODO: add more client-specific data (player info, team info, etc.)
} t_client;

void client_init(t_client *client, int socket_fd);
void client_destroy(t_client *client);

#endif //CLIENT_H

/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** game.h
*/

#ifndef GAME_H_
    #define GAME_H_

    //Include all the libraries needed here
    #include <stdio.h>
    #include <string.h>

typedef struct s_client t_client;
typedef struct s_server t_server;
typedef struct my_timer_s my_timer_t;

typedef struct s_teams {
    t_client *players;
    unsigned nb_players;
    unsigned max_players;
    char *name;
} t_teams;

typedef struct t_map {
    unsigned x;
    unsigned y;
    unsigned player;
    unsigned egg;
    unsigned resources[TOTAL_RESOURCES];
} t_map;

typedef struct s_game {
    t_teams *teams;
    t_map *tiles;
} t_game;

typedef struct gui_command {
    char *command_id;
    void (*function)(t_server *, char **, int);
} gui_command;

typedef struct ai_command {
    char *command_id;
    void (*function_ai)(t_server *, char **, int);
    double time;
} ai_command;

#endif /* !GAME_H_ */

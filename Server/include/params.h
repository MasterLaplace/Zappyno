/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** params.h
*/

#ifndef PARAMS_H
    #define PARAMS_H

//Include all the libraries you need here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/**
 * Structure for the params
 */
typedef struct s_params {
    int port;
    int width;
    int height;
    int clientsNb;
    int freq;
    char **team_names;
    int num_teams;
}   t_params;

/**
 * Structure for pointer to function
 */
typedef struct s_opt {
    char opt;
    void (*f)(char *, t_params *);
} t_opt;

//Prototypes src/parser_params/ | function made to parse the params
void handle_n(char **argv, int optind, int argc, t_params *params);
void handle_f(char *optarg, t_params *params);
void handle_c(char *optarg, t_params *params);
void handle_y(char *optarg, t_params *params);
void handle_x(char *optarg, t_params *params);
void handle_p(char *optarg, t_params *params);
void parse_args(int argc, char *argv[], t_params *params);
void check_params(t_params *params);
void display_params(t_params params);

#endif //PARAMS_H
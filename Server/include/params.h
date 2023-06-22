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
 *
 * @param width the width
 * @param height the height
 * @param clientsNb the clientsNb
 * @param freq the freq
 * @param num_teams the num_teams
 * @param team_names the team_names
 * @param port the port
 */
typedef struct s_params {
    unsigned width;
    unsigned height;
    unsigned clientsNb;
    unsigned freq;
    unsigned num_teams;
    char **team_names;
    short port;
}   t_params;

/**
 * Structure for pointer to function
 *
 * @param opt the option
 * @param f the function
 */
typedef struct s_opt {
    char opt;
    void (*f)(char *, t_params *);
} t_opt;

//Prototypes src/parser_params/ | function made to parse the params
void handle_f(char *optarg, t_params *params);
void handle_c(char *optarg, t_params *params);
void handle_y(char *optarg, t_params *params);
void handle_x(char *optarg, t_params *params);
void handle_p(char *optarg, t_params *params);
void parse_args(int argc, char *argv[], t_params *params);
void check_params(t_params *params);
void display_params(t_params params);

#endif //PARAMS_H

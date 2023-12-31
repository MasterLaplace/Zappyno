/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** flags_params_next.c
*/

#include "../../include/main.h"

/**
 * Pointer to function
 */
t_opt opts[] = {
    {'p', &handle_p},
    {'x', &handle_x},
    {'y', &handle_y},
    {'c', &handle_c},
    {'f', &handle_f},
    {0, NULL}
};

/**
 * Handle the -n flag
 * @param argv
 * @param optind
 * @param argc
 * @param params
 */
static void handle_n(char **argv, int optind, int argc, t_params *params)
{
    for (int i = optind - 1; i < argc; i++) {
        if (argv[i][0] == '-')
            break;
        params->team_names = realloc(params->team_names, sizeof(char*) * (params->num_teams + 1));
        if (!params->team_names)
            exit(EXIT_ERROR);
        params->team_names[params->num_teams] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
        if (!params->team_names[params->num_teams])
            exit(EXIT_ERROR);
        strcpy(params->team_names[params->num_teams],argv[i]);
        params->num_teams++;
    }
    params->team_names = realloc(params->team_names, sizeof(char*) * (params->num_teams + 1));
    if (!params->team_names)
        exit(EXIT_ERROR);
    params->team_names[params->num_teams] = NULL;
}

static void check_operator(int argc, char *argv[], t_params *params, int opt)
{
    for (unsigned i = 0; opts[i].opt; i++) {
        if (opt == 'n') {
            handle_n(argv, optind, argc, params);
            break;
        }
        if (opt == opts[i].opt) {
            opts[i].f(optarg, params);
            break;
        }
    }
}

/**
 * Parse the arguments and fill the params structure
 * @param argc
 * @param argv
 * @param params
 */
void parse_args(int argc, char *argv[], t_params *params)
{
    int opt;

    while ((opt = getopt(argc, argv, "p:x:y:c:f:n:")) != -1)
        check_operator(argc, argv, params, opt);
}

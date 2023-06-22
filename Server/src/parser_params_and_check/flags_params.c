/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** flags_params_next.c
*/

#include "../../include/params.h"

/**
 * Handle the -p flag
 * @param optarg
 * @param params
 */
void handle_p(char *optarg, t_params *params)
{
    params->port = atoi(optarg);
}

/**
 * Handle the -x flag
 * @param optarg
 * @param params
 */
void handle_x(char *optarg, t_params *params)
{
    params->width = atoi(optarg);
}

/**
 * Handle the -y flag
 * @param optarg
 * @param params
 */
void handle_y(char *optarg, t_params *params)
{
    params->height = atoi(optarg);
}

/**
 * Handle the -c flag
 * @param optarg
 * @param params
 */
void handle_c(char *optarg, t_params *params)
{
    params->clientsNb = atoi(optarg);
}

/**
 * Handle the -f flag
 * @param optarg
 * @param params
 */
void handle_f(char *optarg, t_params *params)
{
    params->freq = atoi(optarg);
}

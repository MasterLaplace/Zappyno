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
    long tmp = atol(optarg);

    if (tmp < 0 || tmp > 65535) {
        printf("Port must be between 0 and 65535\n");
        exit(84);
    }
    params->port = tmp;
}

/**
 * Handle the -x flag
 * @param optarg
 * @param params
 */
void handle_x(char *optarg, t_params *params)
{
    params->width = atoi(optarg);
    if (params->width < 10 || params->width > 30) {
        printf("Width must be between 10 and 30\n");
        exit(EXIT_ERROR);
    }
}

/**
 * Handle the -y flag
 * @param optarg
 * @param params
 */
void handle_y(char *optarg, t_params *params)
{
    params->height = atoi(optarg);
    if (params->height < 10 || params->height > 30) {
        printf("Height must be between 10 and 30\n");
        exit(EXIT_ERROR);
    }
}

/**
 * Handle the -c flag
 * @param optarg
 * @param params
 */
void handle_c(char *optarg, t_params *params)
{
    params->clientsNb = atoi(optarg);
    if (params->clientsNb < 1) {
        printf("ClientsNb must be greater than 0\n");
        exit(EXIT_ERROR);
    }
}

/**
 * Handle the -f flag
 * @param optarg
 * @param params
 */
void handle_f(char *optarg, t_params *params)
{
    params->freq = atoi(optarg);
    if (params->freq < 1 || params->freq > 10000) {
        printf("Freq must be greater than 0 and less than 10000\n");
        exit(EXIT_ERROR);
    }
}

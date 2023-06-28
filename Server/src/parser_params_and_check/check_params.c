/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** flags_params_next.c
*/

#include "../../include/main.h"

/**
 * Display the parameters
 * @param params
 */
void display_params(t_params params)
{
    printf("port: %d\n", params.port);
    printf("width: %d\n", params.width);
    printf("height: %d\n", params.height);
    printf("clientsNb: %d\n", params.clientsNb);
    printf("freq: %d\n", params.freq);
    printf("num_teams: %d\n", params.num_teams);
    for (unsigned i = 0; i < params.num_teams; i++)
        printf("team_names[%d]: %s\n", i, params.team_names[i]);
}

/**
 * Check if the parameters are valid
 * @param params
 */
void check_params(t_params *params)
{
    bool check = false;
    if (params->width == 0 || params->height == 0 ||
        params->clientsNb == 0 || params->freq == 0 || params->num_teams == 0)
        check = true;
    if (params->port < 1024)
        check = true;
    if (params->width < 10 || params->width > 30)
        check = true;
    if (params->height < 10 || params->height > 30)
        check = true;
    if (params->freq < 2 || params->freq > 1000)
        check = true;
    if (check == true) {
        printf("Error: invalid parameters\n");
        exit(EXIT_ERROR);
    }
}

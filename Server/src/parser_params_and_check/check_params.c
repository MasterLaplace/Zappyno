/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** flags_params_next.c
*/

#include "../../include/main.h"

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
    if (params->port < 1024 || params->port > 65535)
        check = true;
    if (params->width < 10 || params->width > 1920)
        check = true;
    if (params->height < 10 || params->height > 1080)
        check = true;
    if (params->freq < 2 || params->freq > 1000)
        check = true;
    if (check == true) {
        printf("Error: invalid parameters\n");
        exit(84);
    }
}
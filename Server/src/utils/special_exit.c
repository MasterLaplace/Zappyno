/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** special_exit
*/

#include "../../include/main.h"

void exit_malloc(void)
{
    printf("Error: malloc failed\n");
    printf("%s\n", HELP);
    exit(EXIT_ERROR);
}

void exit_timer(void)
{
    printf("Error: timer failed\n");
    printf("%s\n", HELP);
    exit(EXIT_ERROR);
}

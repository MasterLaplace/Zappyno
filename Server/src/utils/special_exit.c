/*
** EPITECH PROJECT, 2023
** Zappyno
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

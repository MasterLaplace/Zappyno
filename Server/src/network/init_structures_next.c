/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** init_structures.c
*/

#include "../../include/main.h"
#include "signal.h"
#include <time.h>

void return_for_exit(UNUSED int sig)
{
    printf("Server is closing...\n");
    exit(EXIT_SUCCESS);
}

void init(void)
{
    printf("Server is starting...\n");
    srand(time(NULL));
    signal(SIGPIPE, return_for_exit);
    signal(SIGINT, return_for_exit);
}

void clean(void)
{
    printf("Server is closing...\n");
    t_server *ptr = (t_server *)get_environment_variable("SERVER_PTR");
    free_server(&ptr);
}

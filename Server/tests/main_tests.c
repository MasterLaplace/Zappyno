/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main_tests.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/main.h"

Test(MainTest, main)
{
    int ac = 2;
    char *av[2] = {(char *) "./zappy_server", (char *) "-h"};

    cr_assert(main(ac, av) == EXIT_SUCCESS, "\033[1;31mmain should return EXIT_SUCCESS.\033[0m");
}

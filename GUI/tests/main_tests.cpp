/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main_tests.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/main.cpp"

Test(MainTest, main)
{
    int ac = 2;
    const char *av[2] = {(char *) "./zappy_gui", (char *) "-h"};

    cr_assert(main(ac, av) == EXIT_SUCCESS, "\033[1;31mmain should return EXIT_SUCCESS.\033[0m");
}

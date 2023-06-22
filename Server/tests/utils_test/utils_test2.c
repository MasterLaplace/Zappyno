/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** utils_test2
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../include/server.h"

Test(UtilsTest, wrap_x)
{
    int x = -3;

    cr_assert(wrap_x(x, 10) == 0.7, "\033[1;31mwrap_x should return 0.7.\033[0m");
}

Test(UtilsTest, wrap_y)
{
    int y = 9;

    cr_assert(wrap_y(y, 10) == 9, "\033[1;31mwrap_y should return 9.\033[0m");
}

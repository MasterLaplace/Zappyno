/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** utils_test1
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../../include/server.h"

Test(UtilsTest, my_nblen)
{
    int nb = 333;

    cr_assert(my_nblen(nb) == 3, "\033[1;31mmy_nblen should return 3.\033[0m");
}

Test(UtilsTest, itoa)
{
    int nb = 333;

    cr_assert(itoa(nb) == 3, "\033[1;31mitoa should return \"333\".\033[0m");
}

Test(UtilsTest, count_words)
{
    char *words = "hello world friends!";

    cr_assert(count_words(words, " ") == 3, "\033[1;31mcount_words should return 3.\033[0m");
}

// Test(UtilsTest, stwa)
// {
//     char *words = "hello world friends!";

//     cr_assert(stwa(words, " ") == 3, "\033[1;31mstwa should return 3.\033[0m");
// }

Test(UtilsTest, my_strcat)
{
    char *dest = "hello ";
    char *src = "world!";

    cr_assert(strcmp(my_strcat(dest, src), "hello world!"), "\033[1;31mmy_strcat should return \"hello world!\".\033[0m");
}

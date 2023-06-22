/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** itoa
*/

#include "../../include/server.h"

int my_nblen(int nb)
{
    int i = 0;
    int tmp = nb;

    if (nb == 0)
        return 1;
    for (; tmp > 0; i++) {
        tmp = tmp / 10;
    }
    for (; tmp < 0; i++) {
        tmp = tmp / 10;
    }
    return i;
}

char *itoa(int nb)
{
    int len = my_nblen(nb);
    int tmp = 0;
    int place = 0;
    char *nb_str = malloc(sizeof(char) * len + 1);

    if (!nb_str)
        return NULL;
    if (nb < 0) {
        nb_str[0] = '-';
        nb *= -1;
    }
    for (int i = len + place; i > place; i--) {
        tmp = nb;
        tmp %= 10;
        nb_str[i - 1] = tmp + '0';
        nb /= 10;
    }
    nb_str[len + place] = '\0';
    return nb_str;
}

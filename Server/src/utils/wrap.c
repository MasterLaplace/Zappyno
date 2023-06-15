/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** wrap.c
*/

#include "../../include/server.h"

int wrap_x(int x, int width)
{
    if (x < 0) {
        return (x + width) % width;
    } else if (x >= width) {
        return x % width;
    }
    return x;
}

int wrap_y(int y, int height)
{
    if (y < 0) {
        return (y + height) % height;
    } else if (y >= height) {
        return y % height;
    }
    return y;
}

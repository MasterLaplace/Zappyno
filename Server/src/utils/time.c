/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** stwa.c
*/

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>

#define TIMEOUT 5

struct timeval timestamp;

bool has_timed_out(clock_t delay)
{
    clock_t curr_time = clock();
    double time_taken = ((double)curr_time - delay) / CLOCKS_PER_SEC;
    return time_taken >= 3.0;
}

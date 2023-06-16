/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** timer.c
*/

#include "../../include/server.h"
#include <time.h>

bool has_timer_expired(t_client *player)
{
    if (!player)
        return !printf("No player\n");
    if (!player->timer.duration)
        return false;
    if (player->timer.duration == -1) {
        player->timer.start = 0;
        player->timer.duration = 0;
        return true;
    }
    printf("start: %ld | end: %ld\n", player->timer.start, time(NULL));
    if (difftime(time(NULL), player->timer.start) >=
        player->timer.duration) {
        printf("Timer expired\n");
        player->timer.start = 0;
        player->timer.duration = 0;
        return true;
    }
    return false;
}

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
    if (!player->timer)
        return !printf("No timer\n");
    if (!player->timer->duration)
        return !printf("No duration\n");

    printf("start: %ld | end: %ld\n", player->timer->start, time(NULL));
    if (difftime(time(NULL), player->timer->start) >=
        player->timer->duration) {
        printf("Timer expired\n");
        return true;
    }
    return false;
}

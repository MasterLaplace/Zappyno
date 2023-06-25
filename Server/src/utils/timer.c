/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** timer.c
*/

#include "../../include/server.h"
#include <time.h>

bool has_timer_expired_gen_food(server_timer_t *timer, double duration)
{
    if (!timer)
        return false;
    if (difftime(time(NULL), timer->start) >=
        duration) {
        timer->start = time(NULL);
        if (timer->start == -1)
            return false;
        return true;
    }
    return false;
}

bool has_timer_expired(t_client *player)
{
    if (!player)
        return !printf("No player\n");
    if (player->timer.duration == 0) {
        return false;
    }
    if (difftime(time(NULL), player->timer.start) >=
        player->timer.duration) {
        printf("Timer expired\n");
        player->timer.start = 0;
        player->timer.duration = 0;
        return true;
    }
    return false;
}

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
    if (duration == -1) {
        timer->start = time(NULL);
        return true;
    }
    //printf("start: %ld | end: %ld\n", server->timer.start, time(NULL));
    if (difftime(time(NULL), timer->start) >=
        duration) {
        //printf("Timer expired\n");
        timer->start = time(NULL);
        return true;
    }
    return false;
}


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
    //printf("start: %ld | end: %ld\n", player->timer.start, time(NULL));
    if (difftime(time(NULL), player->timer.start) >=
        player->timer.duration) {
        printf("Timer expired\n");
        player->timer.start = 0;
        player->timer.duration = 0;
        return true;
    }
    return false;
}

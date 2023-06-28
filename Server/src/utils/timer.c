/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** timer.c
*/

#include "../../include/server.h"
#include <time.h>
#include <math.h>

bool has_timer_expired_gen_food(server_timer_t *timer, double duration)
{
    double wait_time = (double)(clock() - timer->start) / CLOCKS_PER_SEC;

    if (wait_time >= duration) {
        timer->start = clock();
        return true;
    }
    return false;
}


bool has_timer_expired(t_client *player)
{
    if (!player)
        return !printf("No player\n");
    if (player->timer.duration == 0)
        return false;
    double wait_time = (clock() - player->timer.start) / CLOCKS_PER_SEC;
    if (wait_time >= player->timer.duration) {
        player->timer.start = clock();
        player->timer.duration = 0;
        return true;
    }
    return false;
}

double calcul_angle(int x, int y)
{
    double angle_radians = atan2(y, x);

    if (angle_radians < 0)
        angle_radians += 2 * M_PI;
    return angle_radians * 180 / M_PI;
}

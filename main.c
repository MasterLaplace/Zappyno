/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** main
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct point {
    int x;
    int y;
} pt;

// tu regarde du coté gauche en traversant la map
// tu regarde du coté droit en traversant la map
int check_x(int e_x, int r_x, int map_size) {
    int left_len, right_len = 0;
    for (int i = e_x, j = e_x; i < map_size + e_x; i++, j++) {
        if (j == map_size)
            j = 0;
        if (j == r_x) {
            left_len = i - e_x;
            break;
        }
    }
    for (int i = e_x, j = e_x; i > e_x - map_size; i--, j--) {
        if (j == 0)
            j = map_size - 1;
        if (j == r_x) {
            right_len = e_x - i;
            break;
        }
    }
    if (left_len == 0 && right_len != 0)
        return (-right_len);
    if (ABS(left_len) < ABS(right_len) || (right_len == 0 && left_len != 0))
        return (left_len);
    return (-right_len);
}
// tu regarde vert le haut en traversant la map
// tu regarde vert le bas en traversant la map
int check_y(int e_y, int r_y, int map_size) {
    int up_len, down_len = 0;
    for (int i = e_y, j = e_y; i < map_size + e_y; i++, j++) {
        if (j == map_size)
            j = 0;
        if (j == r_y) {
            up_len = i - e_y;
            break;
        }
    }
    for (int i = e_y, j = e_y; i > e_y - map_size; i--, j--) {
        if (j == 0)
            j = map_size - 1;
        if (j == r_y) {
            down_len = e_y - i;
            break;
        }
    }
    if (up_len == 0 && down_len != 0)
        return (down_len);
    if (ABS(up_len) < ABS(down_len) || (down_len == 0 && up_len != 0))
        return (-up_len);
    return (down_len);
}
// tu tri les directions en fonction de la distance
// tu prend la plus courte

double calcul_angle(int x, int y)
{
    double angle_radians = atan2(y, x);

    if (angle_radians < 0)
        angle_radians += 2 * M_PI;

    return angle_radians * 180 / M_PI;
}

int result(int orientation, double angle)
{
    static const int DIR[4][8] = {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 5, 6, 7, 8, 1, 2, 3, 4 },
        { 3, 4, 5, 6, 7, 8, 1, 2 },
        { 7, 8, 1, 2, 3, 4, 5, 6 },
    };

    if ((angle > 315 && angle < 365) || (angle > 0 && angle < 45))
        return DIR[orientation - 1][0];
    if (angle == 315)
        return DIR[orientation - 1][1];
    if (angle == 225)
        return DIR[orientation - 1][3];
    if (angle == 45)
        return DIR[orientation - 1][7];
    if (angle == 135)
        return DIR[orientation - 1][5];
    if ((angle < 225 && angle > 135))
        return DIR[orientation - 1][4];
    if ((angle < 315 && angle > 225))
        return DIR[orientation - 1][2];
    if ((angle > 135 && angle < 45))
        return DIR[orientation - 1][6];
}

int main(void) {
    pt em = {3, 9};
    pt re = {6, 3};

    int em_dir = 1; // 1 = north, 2 = east, 3 = south, 4 = west
    int re_dir = 2; // 1 = north, 2 = east, 3 = south, 4 = west

    int map_size = 10;

    int x = check_x(em.x, re.x, map_size);
    int y = check_y(em.y, re.y, map_size);

    return result(em_dir, calcul_angle(x, y));
}

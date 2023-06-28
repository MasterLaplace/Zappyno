/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** env_utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void set_environment_variable(const char *key, void *ptr)
{
    uintptr_t entier = (uintptr_t)ptr;
    char str[16];

    memset(str, 0, 16);
    sprintf(str, "%p", (void *)entier);
    setenv(key, str, 1);
}

uintptr_t get_environment_variable(const char *key)
{
    char *env = getenv(key);

    if (!env)
        return (0x0);
    return (uintptr_t)strtoull(env, NULL, 16);
}

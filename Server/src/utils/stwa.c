/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** stwa.c
*/

#include <string.h>
#include <stdlib.h>

static unsigned count_words(char *str, const char *delim)
{
    char *str_dup = NULL;
    unsigned count = 0;

    if (!str)
        return (0);
    str_dup = strdup(str);
    if (!str_dup)
        return (0);
    if (strtok(str_dup, delim))
        count++;
    for (; strtok(NULL, delim); count++);
    free(str_dup);
    return count;
}

char **stwa(char *str, const char *delim)
{
    unsigned len = count_words(str, delim);
    char **words = malloc(sizeof(char *) * (len + 1));
    char *str_dup = NULL;

    if (len == 0) {
        free(words);
        return (NULL);
    }
    str_dup = strdup(str);
    if (!str_dup)
        return (NULL);
    words[0] = strdup(strtok(str_dup, delim));
    if (!words[0])
        return (NULL);
    for (unsigned i = 1; i < len; ++i)
        words[i] = strdup(strtok(NULL, delim));
    words[len] = NULL;
    free(str_dup);
    return words;
}

char *my_strcat(char *dest, char *src)
{
    char *tmp = malloc(sizeof(char) * (strlen(dest) + strlen(src) + 1));
    unsigned i = 0;
    unsigned e = 0;

    if (!tmp)
        return (NULL);

    for (; src && src[i]; ++i)
        tmp[i] = src[i];
    for (; dest && dest[e]; ++i, ++e)
        tmp[i] = dest[e];
    tmp[i] = '\0';
    if (dest)
        free(dest);
    return tmp;
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_name_of_all_the_teams
*/

#include "../../../include/send_package.h"

// count all words size for number of char in all team names
size_t count_all_words_size(char **array)
{
    size_t count = 0;

    for (size_t i = 0; array[i] != NULL; i++)
        count += strlen(array[i]);
    return count;
}

// return the size of the final mesage + 1 for \0
size_t count_message_size(char **array, t_server *server)
{
    size_t res = (server->params->num_teams * 5) +
count_all_words_size(array) + 2;
    return res;
}

void send_name_of_all_the_teams(t_server *server, UNUSED char **array, int id)
{
    AUTO_FREE char *message = calloc(count_message_size(
server->params->team_names, server), sizeof(char));
    if (!message)
        return;
    for (size_t i = 0; server->params->team_names[i] != NULL; i++) {
        strncat(message, "tna ",strlen(message) + 4);
        strncat(message, server->params->team_names[i],strlen(message)
+ strlen(server->params->team_names[i]));
        strncat(message, "\n",strlen(message) + 1);
    }
    send_to_gui(server, message, id);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_name_of_all_the_teams
*/

#include "../../include/send_package.h"

// count all words size for number of char in all team names
size_t count_all_words_size(char **array)
{
    size_t count = 0;

    for(size_t i = 0; array[i] != NULL; i++)
        count += strlen(array[i]);
    return count;
}

// return the size of the final mesage + 1 for \0
size_t count_message_size(char **array, t_server *server)
{
    size_t res = (server->params->num_teams * 5) + count_all_words_size(array) + 1;
    return res;
}

void send_name_of_all_the_teams(t_server *server, char** array)
{
    (void)array;
    char *message = calloc(
    count_message_size(server->params->team_names, server), sizeof(char));

    for (size_t i = 0; server->params->team_names[i] != NULL; i++) {
        strncat(message, "tna ",strlen(message) + 4);
        strncat(message, server->params->team_names[i],strlen(message)
        + strlen(server->params->team_names[i]));
        strncat(message, "\n",strlen(message) + 1);
    }
    sprintf(message, "%s", message);
    send_to_client(server, message, server->id);
}

void send_name_of_all_the_teams_to_all(t_server *server, char** array)
{
    (void)array;
    size_t z = 0;
    char *message = calloc(
    count_message_size(server->params->team_names, server), sizeof(char));

    for (size_t i = 0; server->params->team_names[i] != NULL; i++) {
        message[z] = 't';
        message[z + 1] = 'n';
        message[z + 2] = 'a';
        message[z] = ' ';
        z += 4;
        for (size_t y = 0; server->params->team_names[i][y] != '\0'; i++) {
            message[z] = server->params->team_names[i][y];
            z++;
        }
        message[z] = '\n';
        z++;
    }
    message[z] = '\0';
    sprintf(message, "tna %s\n", message);
<<<<<<< Updated upstream
    send_to_client(server, message, server->id);
=======
>>>>>>> Stashed changes
    send_to_all_clients(server, message);
}

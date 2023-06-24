/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"
#include <time.h>
#include <errno.h>


ai_command ia_client[] = {
    {"Look", recv_look, 1},
    {"Forward", recv_forward, 1},
    {"Right", recv_right, 1},
    {"Left", recv_left, 1},
    {"Inventory", recv_inventory, 1},
    {"Connect_nbr", recv_connect_nbr, -1},
    {"Take", recv_take, 1},
    {"Set", recv_set, 1},
    {"Broadcast", recv_broadcast, 1},
    {"Fork", recv_fork, 1},
    {"Eject", recv_eject, 1},
    {"Incantation", recv_incantation, 1},
    {NULL, NULL, 0}
};

static void check_command_ai_next(t_server *server, char **message, int i)
{
    CLIENT(server->id).function = NULL;
    CLIENT(server->id).function = ia_client[i].function_ai;
    CLIENT(server->id).timer.start = time(NULL);
    if (CLIENT(server->id).timer.start == -1)
        return;
    CLIENT(server->id).timer.duration = ia_client[i].time;
    printf("Timer set to %f\n", CLIENT(server->id).timer.duration);
    if (CLIENT(server->id).params_function != NULL)
        free_double_array(&CLIENT(server->id).params_function);
    CLIENT(server->id).params_function = copy_array(message);
    if (!CLIENT(server->id).params_function)
        return;
}

static void check_command_ai(t_server *server, char **message)
{
    for (int i = 0; ia_client[i].command_id; i++) {
        if (!strncmp(ia_client[i].command_id, message[0],
strlen(ia_client[i].command_id)) && !CLIENT(server->id).is_freezed &&
ia_client[i].time == -1.0) {
            printf("Command found : %s\n", ia_client[i].command_id);
            ia_client[i].function_ai(server, message);
            return;
        }
        if (!strncmp(ia_client[i].command_id, message[0],
strlen(ia_client[i].command_id)) && !CLIENT(server->id).is_freezed) {
            printf("Command found : %s\n", ia_client[i].command_id);
            check_command_ai_next(server, message, i);
            return;
        }
    }
}

static void receive_from_client_next(t_server *server, char *message,
int current_buf_len, int message_len)
{
    printf("ok\n");
    server->clients[server->id].buffer = realloc(
server->clients[server->id].buffer,current_buf_len + message_len + 1);
    if (!server->clients[server->id].buffer)
        return;
    ON_CLEANUP(free_double_array) char **mes = stwa(strcat(
server->clients[server->id].buffer, message), " \n\t");
    if (!mes)
        return;
    printf("ok3\n");
    if (!CLIENT(server->id).is_connected) {
        join_client(server, mes);
    } else {
        printf("Message received buf: %s\n", server->clients[server->id].buffer);
        if (!CLIENT(server->id).is_gui)
            check_command_ai(server, mes);
        else
            check_command_gui(server, mes);
    }
    if (server->clients[server->id].buffer != NULL) {
        free(server->clients[server->id].buffer);
        server->clients[server->id].buffer = calloc(1, 1);
        if (!server->clients[server->id].buffer)
            return;
    }
}

void receive_from_client(t_server *server, char *message)
{
    size_t current_buf_len = 0;
    size_t mes_len = strlen(message);
    if (server->clients[server->id].buffer != NULL)
        current_buf_len = strlen(server->clients[server->id].buffer);
    if (!strstr(message, "\n")) {
        server->clients[server->id].buffer = realloc(
server->clients[server->id].buffer,current_buf_len + mes_len + 1);
        if (!server->clients[server->id].buffer)
            return;
        strcat(server->clients[server->id].buffer, message);
    } else {
        receive_from_client_next(server, message, current_buf_len, mes_len);
    }
}

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 */
void handle_client_data(t_server *server, int fd)
{
    char message[2];
    int valread;
    printf("fd : %d\n", fd);
    if ((valread = read(fd, message, 2)))
        message[valread] = '\0';
    printf("Message received : %s\n", message);
    if (valread == -1) {
        if (errno == ECONNRESET) {
            return remove_client(server, server->id);
        } else {
            perror("recv");
            return;
        }
    } else if (valread == 0) {
        return remove_client(server, server->id);
    } else {
        printf("Message received : %s\n", message);
        receive_from_client(server, message);
    }
    return;
}

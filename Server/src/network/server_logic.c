/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** server_logic.c
*/

#include "../../include/recv_package.h"
#include "../../include/send_package.h"
#include "../../include/game.h"
#include <time.h>
#include <errno.h>


ai_command ia_client[] = {
    {"Look", recv_look, 0.7},
    {"Forward", recv_forward, 0.7},
    {"Right", recv_right, 0.7},
    {"Left", recv_left, 0.7},
    {"Inventory", recv_inventory, 0.7},
    {"Connect_nbr", recv_connect_nbr, -1.0},
    {"Take", recv_take, 0.7},
    {"Set", recv_set, 0.7},
    {"Broadcast", recv_broadcast, 0.7},
    {"Fork", recv_fork, 4.2},
    {"Eject", recv_eject, 0.7},
    {"Incantation", recv_incantation, 30.0},
    {NULL, NULL, 0.0}
};

static void check_command_ai_next(t_server *server, char **message, unsigned i,
int id)
{
    CLIENT(id).function = NULL;
    CLIENT(id).function = ia_client[i].function_ai;
    CLIENT(id).timer.duration = ia_client[i].time / server->params->freq;
    if (CLIENT(id).params_function)
        free_double_array(&CLIENT(id).params_function);
    CLIENT(id).params_function = copy_array(message);
    if (!CLIENT(id).params_function)
        return;
}

static void check_command_ai(t_server *server, char **message, int id)
{
    for (unsigned i = 0; ia_client[i].command_id; i++) {
        if (!strncmp(ia_client[i].command_id, message[0],
                strlen(ia_client[i].command_id)) && !CLIENT(id).is_freezed &&
                ia_client[i].time == -1.0) {
            ia_client[i].function_ai(server, message, id);
            return;
        }
        if (!strncmp(ia_client[i].command_id, message[0],
                strlen(ia_client[i].command_id)) && !CLIENT(id).is_freezed) {
            check_command_ai_next(server, message, i, id);
            return;
        }
    }
}

static void receive_from_client_next(t_server *server, char *message,
int current_buf_len, int id)
{
    server->clients[id].buffer = realloc(
        server->clients[id].buffer,current_buf_len + strlen(message) + 1
    );
    if (!server->clients[id].buffer)
        return;
    ON_CLEANUP(free_double_array) char **mes = stwa(
        strcat(server->clients[id].buffer, message), " \n\t"
    );
    if (!mes)
        return;
    if (!CLIENT(id).is_connected)
        join_client(server, mes, id);
    else {
        if (!CLIENT(id).is_gui)
            check_command_ai(server, mes, id);
        else
            check_command_gui(server, mes, id);
    }
    if (server->clients[id].buffer) {
        free(server->clients[id].buffer);
        server->clients[id].buffer = calloc(1, 1);
    }
}

void receive_from_client(t_server *server, char *message, int id)
{
    size_t current_buf_len = 0;
    size_t mes_len = strlen(message);

    if (server->clients[id].buffer)
        current_buf_len = strlen(server->clients[id].buffer);
    if (!strstr(message, "\n")) {
        server->clients[id].buffer = realloc(
            server->clients[id].buffer, current_buf_len + mes_len + 1
        );
        if (!server->clients[id].buffer)
            return;
        strcat(server->clients[id].buffer, message);
    } else
        receive_from_client_next(server, message, current_buf_len, id);
}

/**
 * Handle the data received from a client
 * @param server
 * @param fd
 * @param id
 */
void handle_client_data(t_server *server, int fd, int id)
{
    char message[2] = {0};
    int valread;

    if ((valread = read(fd, message, 2)))
        message[valread] = '\0';
    if (valread == -1) {
        if (errno == ECONNRESET)
            return remove_client(server, id);
        else
            return perror("recv");
    } else if (message[0] != '\0')
        receive_from_client(server, message, id);
}

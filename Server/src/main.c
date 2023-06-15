/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"
#include <time.h>

/**
 * Set the params struct to 0
 * @param server
 * @param new_socket
 * @param readfds
 */
void add_client(t_server *server, int new_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (CLIENT(i).socket_fd == 0) {
            CLIENT(i).socket_fd = new_socket;
            server->id = i;
            printf("New client connected : %d\n", new_socket);
            break;
        }
    }
}

void read_data_from_server(t_server *svr, unsigned client_id)
{
    int sd = svr->clients[client_id].socket_fd;

    if (has_timer_expired(&svr->clients[client_id])) {
        svr->clients[client_id].is_freezed = false;
        svr->clients[client_id].timer = NULL;
        svr->clients[client_id].function(svr, NULL);
        svr->clients[client_id].function = NULL;
    }

    if (sd == 0)
        return;
    if (FD_ISSET(sd, &svr->readfds)) {
        handle_client_data(svr, sd);
    }
}

void handle_new_connection(t_server *svr)
{
    int new_socket;

    if ((new_socket = accept(svr->sockfd, NULL, NULL)) >= 0) {

        printf("New connection\n");
        add_client(svr, new_socket);
        send_to_client(svr, "WELCOME\n", svr->id);
    }
}

int set_fds(t_server *svr)
{
    FD_ZERO(&svr->readfds);
    svr->max_fd = svr->sockfd;
    FD_SET(svr->sockfd, &svr->readfds);

    for (unsigned i = 0; i < MAX_CLIENTS; i++) {
        int sd = svr->clients[i].socket_fd;
        if (sd > 0)
            FD_SET(sd, &svr->readfds);
        if (sd > svr->max_fd)
            svr->max_fd = sd;
    }
    return svr->max_fd;
}

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help")))
        return !printf("%s\n", HELP);
    t_params params = set_param_struct();
    parse_args(ac, av, &params);
    check_params(&params);
    t_server *server = set_server_struct(&params);
    setup_server(server, &params);
    while (true) {
        struct timeval timeout = {0};
        timeout.tv_sec = 1;
        if (select(set_fds(server) + 1, &server->readfds,
NULL, NULL, &timeout) < 0)
            perror("select"), exit(EXIT_FAILURE);
        if (FD_ISSET(server->sockfd, &server->readfds))
            handle_new_connection(server);
        for (unsigned i = 0; i < MAX_CLIENTS; i++)
            read_data_from_server(server, i);
    }
}

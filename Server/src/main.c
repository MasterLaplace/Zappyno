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
    for (int i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd == 0) {
            CLIENT(i).socket_fd = new_socket;
            server->id = i;
            server->clients[i].params_function = NULL;
            printf("New client connected : %d\n", new_socket);
            break;
        }
    }
}

bool read_data_from_server(t_server *svr, unsigned client_id)
{
    int sd = svr->clients[client_id].socket_fd;

    if (has_timer_expired_gen_food(svr, svr->timer.duration_gen_food)) {
        generate_food(svr);
        for (int i = 0; i < svr->params->width * svr->params->height; i++) {
            printf("Tile %d: x: %d y: %d | ", i, svr->game.tiles[i].x, svr->game.tiles[i].y);
            printf("food: %d | ", svr->game.tiles[i].resources[0]);
            printf("linemate: %d | ", svr->game.tiles[i].resources[1]);
            printf("deraumere: %d | ", svr->game.tiles[i].resources[2]);
            printf("sibur: %d | ", svr->game.tiles[i].resources[3]);
            printf("mendiane: %d | ", svr->game.tiles[i].resources[4]);
            printf("phiras: %d | ", svr->game.tiles[i].resources[5]);
            printf("thystame: %d\n", svr->game.tiles[i].resources[6]);
        }
    }
    if (has_timer_expired_gen_food(svr, svr->timer.remove_food)) {
        svr->clients[svr->id].resources[0] -= 1;
        printf("Food removed\n");
    }
    if (has_timer_expired(&svr->clients[client_id])) {
        svr->clients[client_id].function(svr, svr->clients[client_id].params_function);
        svr->clients[client_id].is_freezed = false;
        svr->clients[client_id].function = NULL;
        if (svr->clients[client_id].params_function != NULL)
            free_double_array(&svr->clients[client_id].params_function);
        svr->clients[client_id].params_function = NULL;
    }
    if (sd == 0)
        return true;
    if (FD_ISSET(sd, &svr->readfds)) {
        return handle_client_data(svr, sd);
    }
    return true;
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

    for (unsigned i = 0; i < SOMAXCONN; i++) {
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
    ON_CLEANUP(free_server) t_server *server = set_server_struct(&params);
    setup_server(server, &params);
    bool tmp = true;
    while (tmp) {
        struct timeval timeout = {0};
        timeout.tv_sec = 1;
        if (select(set_fds(server) + 1, &server->readfds,
NULL, NULL, &timeout) < 0)
            perror("select"), exit(EXIT_FAILURE);
        if (FD_ISSET(server->sockfd, &server->readfds))
            handle_new_connection(server);
        for (unsigned i = 0; i < SOMAXCONN; i++)
            tmp &= read_data_from_server(server, i);
    }
    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (server->clients[i].params_function)
            free_double_array(&server->clients[i].params_function);
    }
    return EXIT_SUCCESS;
}

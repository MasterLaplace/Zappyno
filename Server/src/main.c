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

bool check_death(t_server *server)
{
    if (TEAM_INDEX == -1 || INDEX_IN_TEAM == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] <= 0 && has_timer_expired_gen_food(&server->remove_food_timer, server->remove_food_timer.duration)) {
        AUTO_FREE char *str = calloc(my_nblen(server->id) + 10, sizeof(char));
        sprintf(str, "pdi %d\n", server->id);
        printf("Player %d died\n", server->id);
        send_to_all_gui(server, str);
        remove_client(server, server->id);
        return true;
    }
    return false;
}

bool read_data_from_server(t_server *server, unsigned client_id)
{
    int sd = server->clients[client_id].socket_fd;

    if (check_death(server))
        return true;
    if (has_timer_expired_gen_food(&server->remove_food_timer, server->remove_food_timer.duration)) {
        if (TEAM_INDEX != -1 && INDEX_IN_TEAM != -1) {
            if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id != -1) {
                TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] -= 1;
                printf("Remove food\n");
            }
        }
    }
    if (has_timer_expired_gen_food(&server->gen_food_timer, server->gen_food_timer.duration)) {
        printf("Generate food\n");
        generate_food(server);
    }
    if (has_timer_expired(&server->clients[client_id])) {
        server->clients[client_id].function(server, server->clients[client_id].params_function);
        server->clients[client_id].is_freezed = false;
        server->clients[client_id].function = NULL;
        if (server->clients[client_id].params_function != NULL)
            free_double_array(&server->clients[client_id].params_function);
        server->clients[client_id].params_function = NULL;
    }
    if (sd == 0)
        return true;
    if (FD_ISSET(sd, &server->readfds)) {
        return handle_client_data(server, sd);
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

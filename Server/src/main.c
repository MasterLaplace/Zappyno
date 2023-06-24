/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"
#include <time.h>
#include "../include/recv_package.h"

/**
 * Set the params struct to 0
 * @param server
 * @param new_socket
 * @param readfds
 */
void add_client(t_server *server, int new_socket)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd == 0 && !CLIENT(i).dead) {
            CLIENT(i).socket_fd = new_socket;
            server->id = i;
            server->clients[i].params_function = NULL;
            break;
        }
    }
}

static bool check_death(t_server *server)
{
    if (TEAM_INDEX == -1 || INDEX_IN_TEAM == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] <= 0 &&
    has_timer_expired_gen_food(&server->remove_food_timer,
server->remove_food_timer.duration)) {
        AUTO_FREE char *str = calloc(my_nblen(server->id) + 10, sizeof(char));
        sprintf(str, "pdi %d\n", server->id);
        send_to_all_gui(server, str);
        send_to_client(server, "dead\n", server->id);
        remove_client(server, server->id);
        return true;
    }
    return false;
}

static void read_data_next(t_server *server, unsigned client_id)
{
    if (check_death(server)) {
        printf("Player %d is dead\n", server->id);
        server->clients[client_id].is_freezed = false;
        server->clients[client_id].function = NULL;
        if (server->clients[client_id].params_function != NULL)
            free_double_array(&server->clients[client_id].params_function);
        server->clients[client_id].params_function = NULL;
        return;
    }
    if (has_timer_expired_gen_food(&server->remove_food_timer,
server->remove_food_timer.duration)) {
        if (TEAM_INDEX != -1 && INDEX_IN_TEAM != -1 &&
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id != -1) {
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] -= 1;
            printf("Remove food\n");
        }
    }
}

static void read_data_from_server(t_server *server, unsigned client_id)
{
    int sd = server->clients[client_id].socket_fd;
    read_data_next(server, client_id);
    /*if (has_timer_expired_gen_food(&server->gen_food_timer,
server->gen_food_timer.duration))
        generate_food(server);*/
    if (has_timer_expired(&server->clients[client_id])) {
        printf("function : %p\n", server->clients[client_id].function);
        server->clients[client_id].function(server,
server->clients[client_id].params_function);
        server->clients[client_id].is_freezed = false;
        server->clients[client_id].function = NULL;
        if (server->clients[client_id].params_function != NULL)
            free_double_array(&server->clients[client_id].params_function);
        server->clients[client_id].params_function = NULL;
    }
    if (sd == 0)
        return;
    if (FD_ISSET(sd, &server->readfds)) {
        handle_client_data(server, sd);
    }
    return;
}

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help")))
        return !printf("%s\n", HELP);
    t_params params = {0};
    parse_args(ac, av, &params);
    check_params(&params);
    t_server *server = set_server_struct(&params);
    if (server == NULL)
        exit_malloc();
    set_environment_variable("SERVER_PTR", server);
    if (!setup_server(server, &params))
        return EXIT_FAILURE;
    do {
        if (select(set_fds(server) + 1, &server->readfds, NULL, NULL, NULL) < 0)
            perror("select");
        if (FD_ISSET(server->sockfd, &server->readfds))
            handle_new_connection(server);
        read_data_from_server(server, server->id);
    } while (true);
}

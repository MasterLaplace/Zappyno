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
            server->clients[i].params_function = NULL;
            send_to_client(server, "WELCOME\n", i);
            break;
        }
    }
}

static bool check_death(t_server *server, int id)
{
    if ((int)TEAM_INDEX == -1 || (int)INDEX_IN_TEAM == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id == -1)
        return false;
    if (TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] <= 0 &&
            has_timer_expired_gen_food(
                &server->remove_food_timer,
                server->remove_food_timer.duration
            ) &&
            FD_ISSET(CLIENT(id).socket_fd, &server->wfd) &&
            FD_ISSET(CLIENT(id).socket_fd, &server->readfds)
        ) {
        AUTO_FREE char *str = (char *)calloc(my_nblen(id) + 10, sizeof(char));
        sprintf(str, "pdi %d\n", id);
        send_to_all_gui(server, str);
        send_to_client(server, "dead\n", id);
        remove_client(server, id);
        return true;
    }
    return false;
}

static void read_data_next(t_server *server, unsigned id)
{
    if (check_death(server, id)) {
        printf("Player %d is dead\n", id);
        server->clients[id].is_freezed = false;
        server->clients[id].function = NULL;
        if (server->clients[id].params_function)
            free_double_array(&server->clients[id].params_function);
        server->clients[id].params_function = NULL;
    }
    if (has_timer_expired_gen_food(&server->remove_food_timer,
server->remove_food_timer.duration)) {
        if ((int)TEAM_INDEX != -1 && (int)INDEX_IN_TEAM != -1 &&
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].id != -1) {
            TEAMS[TEAM_INDEX].players[INDEX_IN_TEAM].resources[0] -= 1;
            printf("Remove food\n");
        }
    }
}

static void read_data_from_server(t_server *server, unsigned id)
{
    int sd = server->clients[id].socket_fd;
    if (sd == 0)
        return;
    if (FD_ISSET(sd, &server->readfds)) {
        handle_client_data(server, sd, id);
    }
    read_data_next(server, id);
    if (has_timer_expired_gen_food(&server->gen_food_timer, server->gen_food_timer.duration)) {
        printf("[Server] Generate food\n");
        generate_food(server);
    }
    if (has_timer_expired(&server->clients[id])) {
        server->clients[id].function(server, server->clients[id].params_function, id);
        server->clients[id].is_freezed = false;
        server->clients[id].function = NULL;
        if (server->clients[id].params_function)
            free_double_array(&server->clients[id].params_function);
        server->clients[id].params_function = NULL;
    }
    return;
}

void loop(t_server *server)
{
    int nfds = set_fds(server);
    if (select(nfds + 1, &server->readfds, &server->wfd, NULL, NULL) < 0)
        perror("select");
    if (FD_ISSET(server->sockfd, &server->readfds))
        handle_new_connection(server);
    for (int i = 0; i < SOMAXCONN; i++) {
        if (server->clients[i].socket_fd > 0
            && (FD_ISSET(server->clients[i].socket_fd, &server->readfds) ||
            FD_ISSET(server->clients[i].socket_fd, &server->wfd))) {
            read_data_from_server(server, i);
        }
    }
}

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help")))
        return !printf("%s\n", HELP);
    t_params params = {0};
    parse_args(ac, av, &params);
    check_params(&params);
    t_server *server = set_server_struct(&params);
    set_environment_variable("SERVER_PTR", server);
    if (!setup_server(server, &params))
        return EXIT_FAILURE;
    do {
        loop(server);
    } while (true);
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"
#include "signal.h"

/**
 * Set the params struct to 0
 * @return params
 */
t_params set_param_struct(void)
{
    t_params params;
    memset(&params, 0, sizeof(t_params));
    return params;
}

/**
 * Set the game struct to 0
 * @param params
 * @return game
 */
t_game set_game_struct(t_params *params)
{
    t_game game;
    game.teams = malloc(params->num_teams * sizeof(t_teams));
    if (game.teams == NULL) {
        perror("Failed to allocate memory for teams");
        exit(EXIT_FAILURE);
    }
    memset(game.teams, 0, params->num_teams * sizeof(t_teams));
    for (int i = 0; i < params->num_teams; i++) {
        game.teams[i].name = params->team_names[i];
    }
    game.teams->players = malloc(params->clientsNb * sizeof(t_client));
    if (game.teams->players == NULL) {
        perror("Failed to allocate memory for players");
        exit(EXIT_FAILURE);
    }
    memset(game.teams->players, 0, params->clientsNb * sizeof(t_client));
    return game;
}

/**
 * Set the server struct to 0
 * @param params
 * @return server
 */
t_server *set_server_struct(t_params *params)
{
    t_server *server = malloc(sizeof(t_server));
    if (server == NULL) {
        perror("Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }
    server->max_fd = 0;
    server->sockfd = 0;
    memset(server->clients, 0, MAX_CLIENTS * sizeof(t_client));
    server->params = params;
    server->game = set_game_struct(params);
    return server;
}

/**
 * Set the params struct to 0
 * @param server
 * @param new_socket
 * @param readfds
 */
void add_client(t_server *server, int new_socket)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == 0) {
            server->clients[i].socket_fd = new_socket;
            server->id = i;
            printf("New client connected : %d\n", new_socket);
            break;
        }
    }
}

void read_data_from_server(t_server *svr)
{
    char buffer[1025];
    int valread;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = svr->clients[i].socket_fd;

        if (sd == 0)
            continue;
        if (FD_ISSET(sd, &svr->readfds)) {
            handle_client_data(svr, sd);
        }
    }
}

void handle_new_connection(t_server *svr)
{
    int new_socket;

    if (FD_ISSET(svr->sockfd, &svr->readfds)) {
        if ((new_socket = accept(svr->sockfd, NULL, NULL)) >= 0) {
            add_client(svr, new_socket);
            send_to_client(svr, "WELCOME\n");
        }
    }
}

int set_fds(t_server *svr)
{
    FD_ZERO(&svr->readfds);
    svr->max_fd = svr->sockfd;

    FD_SET(svr->sockfd, &svr->readfds);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int sd = svr->clients[i].socket_fd;
        if (sd > 0) {
            FD_SET(sd, &svr->readfds);
        }
        if (sd > svr->max_fd)
            svr->max_fd = sd;
    }
    return svr->max_fd;
}

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        printf("%s\n", HELP);
        return EXIT_SUCCESS;
    }
    t_params params = set_param_struct();
    parse_args(ac, av, &params);
    check_params(&params);
    t_server *server = set_server_struct(&params);

    setup_server(server, &params);
    while (true) {
        signal(SIGPIPE, SIG_IGN);
        int activity = select(set_fds(server) + 1, &server->readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }
        handle_new_connection(server);
        read_data_from_server(server);
    }

    return EXIT_SUCCESS;
}

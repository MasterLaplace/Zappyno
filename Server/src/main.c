/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"

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
void add_client(t_server *server, int new_socket, fd_set *readfds)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].socket_fd == 0) {
            server->clients[i].socket_fd = new_socket;
            server->clients[i].read_fds = *readfds;
            FD_SET(new_socket, readfds);
            printf("New client connected : %d\n", new_socket);
            break;
        }
    }
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
        fd_set readfds;
        server->readfds = readfds;
        FD_ZERO(&readfds);
        FD_SET(server->sockfd, &readfds);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].socket_fd > 0)
                FD_SET(server->clients[i].socket_fd, &readfds);
        }

        // Wait for activity on one of the sockets
        int activity = select(server->max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // If something happened on the server socket, it's an incoming connection
        if (FD_ISSET(server->sockfd, &readfds)) {
            int new_socket = accept(server->sockfd, NULL, NULL);
            if (new_socket < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            // Add the new socket to the array of sockets
            add_client(server, new_socket, &readfds);
        }

        // Else, it's some IO operation on one of the client sockets
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->clients[i].socket_fd > 0 && FD_ISSET(server->clients[i].socket_fd, &readfds)) {
                server->id = i;
                server->game.current_client = &server->clients[i];
                handle_client_data(server, server->clients[i].socket_fd);
            }
        }
    }

    return EXIT_SUCCESS;
}

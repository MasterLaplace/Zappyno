/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.c
*/

#include "../include/main.h"

int main(int ac, char **av)
{
    if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))) {
        printf("%s\n", HELP);
        return EXIT_SUCCESS;
    }
    t_params params;
    params.team_names = NULL;
    params.num_teams = 0;
    t_server *server = malloc(sizeof(t_server));
    server->max_fd = 0;
    server->sockfd = 0;
    for (int i = 0; i < MAX_CLIENTS; i++)
        server->client_sockets[i] = 0;

    parse_args(ac, av, &params);
    check_params(&params);

    printf("port: %d\n", params.port);
    printf("width: %d\n", params.width);
    printf("height: %d\n", params.height);
    printf("clientsNb: %d\n", params.clientsNb);
    printf("freq: %d\n", params.freq);
    printf("num_teams: %d\n", params.num_teams);
    for (int i = 0; i < params.num_teams; i++)
        printf("team_names[%d]: %s\n", i, params.team_names[i]);

    setup_server(server, &params);

    server->clients = malloc(MAX_CLIENTS * sizeof(t_client));
    if (server->clients == NULL) {
        perror("Failed to allocate memory for clients");
        exit(EXIT_FAILURE);
    }
    // The server is set up, handle client connections and data
    while (true) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server->sockfd, &readfds);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (server->client_sockets[i] > 0)
                FD_SET(server->client_sockets[i], &readfds);
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
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (server->client_sockets[i] == 0) {
                    printf("Adding to list of sockets as %d\n", i);
                    server->clients[i].socket_fd = new_socket;
                    server->client_sockets[i] = new_socket;
                    FD_SET(new_socket, &readfds);
                    break;
                }
            }
        }

        // Else, it's some IO operation on one of the client sockets
        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = server->client_sockets[i];
            printf("sd: %d\n", sd);
            if (FD_ISSET(sd, &readfds)) {
                handle_client_data(server, &server->clients[i], sd);
            }
        }
    }

    // Cleanup and free memory
    for (int i = 0; i < params.num_teams; i++)
        free(params.team_names[i]);
    free(params.team_names);

    return EXIT_SUCCESS;
}

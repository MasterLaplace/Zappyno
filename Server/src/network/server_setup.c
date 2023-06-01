/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** server_setup.c
*/

#include "../../include/server.h"

/**
 * Create the socket
 * @return the socket fd if success, -1 if error
 */
int create_socket(void) {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Cannot open socket");
        return -1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, "\001", 4) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    return sockfd;
}

/**
 * Bind the socket
 * @param server
 * @param params
 * @return 0 if success, -1 if error
 */
int bind_socket(t_server *server, t_params *params) {
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(params->port);

    if (bind(server->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Cannot bind socket");
        return -1;
    }

    return 0;
}

/**
 * Listen on the socket
 * @param server
 * @param params
 * @return
 */
int listen_socket(t_server *server, t_params *params) {
    if (listen(server->sockfd, params->clientsNb) < 0) {
        perror("Cannot listen on socket");
        return -1;
    }

    return 0;
}

/**
 * Setup the server
 * @param server
 * @param params
 * @return 0 if success, -1 if error
 */
int setup_server(t_server *server, t_params *params) {
    server->sockfd = create_socket();
    if (server->sockfd < 0)
        return -1;

    if (bind_socket(server, params) < 0)
        return -1;

    if (listen_socket(server, params) < 0)
        return -1;

    server->max_fd = server->sockfd;

    printf("Server setup complete\n");

    return 0;
}
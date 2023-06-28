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
int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Cannot open socket");
        return (RETURN_FAILED);
    }
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL failed");
        return (RETURN_FAILED);
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL failed");
        return (RETURN_FAILED);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, "\001", 4) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return (RETURN_FAILED);
    }
    return sockfd;
}

/**
 * Bind the socket
 * @param server
 * @param params
 * @return 0 if success, -1 if error
 */
bool bind_socket(t_server *server, t_params *params)
{
    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(params->port);
    if (bind(server->sockfd, (struct sockaddr *)&serv_addr, 16U) < 0) {
        perror("Cannot bind socket");
        return false;
    }
    return true;
}

/**
 * Listen on the socket
 * @param server
 * @param params
 * @return
 */
bool listen_socket(t_server *server, t_params *params UNUSED)
{
    if (listen(server->sockfd, SOMAXCONN) < 0) {
        perror("Cannot listen on socket");
        return false;
    }
    return true;
}

/**
 * Setup the server
 * @param server
 * @param params
 * @return true if success, false if error
 */
bool setup_server(t_server *server, t_params *params)
{
    server->sockfd = create_socket();
    if (server->sockfd < 0)
        return false;
    if (!bind_socket(server, params))
        return false;
    if (!listen_socket(server, params))
        return false;
    server->max_fd = server->sockfd;
    printf("Server setup complete\n");
    return true;
}

/**
 * Remove a client from the server
 * @param server
 * @param id
 */
void remove_client(t_server *server, int id)
{
    TILES(find_tile(
        server, server->clients[id].pos_x, server->clients[id].pos_y)
    ).player--;
    close(CLIENT(id).socket_fd);
    FD_CLR(CLIENT(id).socket_fd, &server->readfds);
    CLIENT(id).socket_fd = 0;
    server->max_fd = server->sockfd;
    for (unsigned i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd > server->max_fd)
            server->max_fd = CLIENT(i).socket_fd;
    }
    if ((int)TEAM_INDEX >= 0 && (int)INDEX_IN_TEAM >= 0) {
        if (server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].params_function)
            free_double_array(&server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].params_function);
        memset(&server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM], 0, sizeof(t_client));
        if (server->game.teams[TEAM_INDEX].nb_players > 0)
            server->game.teams[TEAM_INDEX].nb_players--;
        memset(&CLIENT(id), 0, sizeof(t_client));
        CLIENT(id).dead = true;
    }
}

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
        return -1;
    }
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL failed");
        return -1;
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL failed");
        return -1;
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, "\001", 4) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return -1;
    }
    return sockfd;
}

/**
 * Bind the socket
 * @param server
 * @param params
 * @return 0 if success, -1 if error
 */
int bind_socket(t_server *server, t_params *params)
{
    struct sockaddr_in serv_addr = {0};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(params->port);
    if (bind(server->sockfd, (struct sockaddr *)&serv_addr, 16U) < 0) {
        perror("Cannot bind socket");
        return (-1);
    }
    return (0);
}

/**
 * Listen on the socket
 * @param server
 * @param params
 * @return
 */
int listen_socket(t_server *server, t_params *params)
{
    if (listen(server->sockfd, SOMAXCONN) < 0) {
        perror("Cannot listen on socket");
        return (-1);
    }
    return (0);
}

/**
 * Setup the server
 * @param server
 * @param params
 * @return 0 if success, -1 if error
 */
bool setup_server(t_server *server, t_params *params)
{
    server->sockfd = create_socket();
    if (server->sockfd < 0)
        return false;
    if (bind_socket(server, params) < 0)
        return false;
    if (listen_socket(server, params) < 0)
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
    int pos = find_tile(server, server->clients[id].pos_x,
server->clients[id].pos_y, id);
    TILES(pos).player--;
    printf("Client %d disconnected\n", id);
    close(CLIENT(id).socket_fd);
    FD_CLR(CLIENT(id).socket_fd, &server->readfds);
    CLIENT(id).socket_fd = 0;
    server->max_fd = server->sockfd;
    for (int i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd > server->max_fd)
            server->max_fd = CLIENT(i).socket_fd;
    }
    if (server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].params_function)
            free_double_array(
&server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM].params_function);
    memset(&server->game.teams[TEAM_INDEX].players[INDEX_IN_TEAM], 0, sizeof(t_client));
    if (server->game.teams[TEAM_INDEX].nb_players > 0)
        server->game.teams[TEAM_INDEX].nb_players--;
    memset(&CLIENT(id), 0, sizeof(t_client));
    CLIENT(id).dead = true;
}

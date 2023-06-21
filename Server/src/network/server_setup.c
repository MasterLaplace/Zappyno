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
int setup_server(t_server *server, t_params *params)
{
    server->sockfd = create_socket();
    if (server->sockfd < 0)
        return (-1);
    if (bind_socket(server, params) < 0)
        return (-1);
    if (listen_socket(server, params) < 0)
        return (-1);
    server->max_fd = server->sockfd;
    printf("Server setup complete\n");
    return (0);
}

/**
 * Remove a client from the server
 * @param server
 * @param id
 */
void remove_client(t_server *server, int id)
{
    int tmp_id = id;
    close(CLIENT(id).socket_fd);
    FD_CLR(CLIENT(id).socket_fd, &server->readfds);
    memset(&CLIENT(id), 0, sizeof(t_client));
    server->max_fd = server->sockfd;
    for (int i = 0; i < SOMAXCONN; i++) {
        if (CLIENT(i).socket_fd > server->max_fd) {
            server->max_fd = CLIENT(i).socket_fd;
        }
    }
    for (int i = 0; i < server->params->num_teams; i++) {
        if (!server->game.teams[i].players)
            continue;
        if (server->game.teams[i].players[INDEX_IN_TEAM].params_function) {
            free_double_array(&server->game.teams[i].players[INDEX_IN_TEAM].params_function);
            server->game.teams[i].players[INDEX_IN_TEAM].socket_fd = 0;
        }
    }
    server->game.teams[TEAM_INDEX].nb_players--;
    CLIENT(tmp_id).dead = true;
}

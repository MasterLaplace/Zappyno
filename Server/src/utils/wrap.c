/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** wrap.c
*/

#include "../../include/server.h"

int wrap_x(int x, int width)
{
    if (x < 0)
        return (x + width) % width;
    else if (x >= width)
        return x % width;
    return x;
}

int wrap_y(int y, int height)
{
    if (y < 0)
        return (y + height) % height;
    else if (y >= height)
        return y % height;
    return y;
}

void reverse_array(int *arr, int size)
{
    int start = 0;
    int end = size - 1;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void handle_new_connection(t_server *svr)
{
    int new_socket;
    int flags;

    if ((new_socket = accept(svr->sockfd, NULL, NULL)) >= 0) {
        printf("New connection\n");
        if ((flags = fcntl(new_socket, F_GETFL, 0)) == -1)
            return perror("fcntl F_GETFL failed");
        if (fcntl(new_socket, F_SETFL, flags | O_NONBLOCK) == -1)
            return perror("fcntl F_SETFL failed");
        add_client(svr, new_socket);
    }
}

int set_fds(t_server *svr)
{
    FD_ZERO(&svr->readfds);
    FD_ZERO(&svr->wfd);
    FD_SET(svr->sockfd, &svr->readfds);
    FD_SET(svr->sockfd, &svr->wfd);
    svr->max_fd = svr->sockfd;

    for (unsigned i = 0; i < SOMAXCONN; i++) {
        int sd = svr->clients[i].socket_fd;
        if (sd > 0) {
            FD_SET(sd, &svr->readfds);
            FD_SET(sd, &svr->wfd);
        }
        if (sd > svr->max_fd)
            svr->max_fd = sd;
    }
    return svr->max_fd;
}

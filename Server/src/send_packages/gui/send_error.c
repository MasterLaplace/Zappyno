/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_error.c
*/

#include "../../../include/send_package.h"

static char ErrorFlag[7][50] = {
    "ko\n",
    "ko Team is full\n",
    "ko Team not exists\n",
    "ko Join gui error\n",
    "ko Join ai error\n",
    "ko Map size error\n",
    "ko Error\n",
};

void send_error(t_server *server, int error_id)
{
    printf("Error: %s", ErrorFlag[error_id]);
    send_to_client(server, ErrorFlag[error_id], server->id);
}

void send_error_to_all(t_server *server, int error_id)
{
    printf("Error: %s", ErrorFlag[error_id]);
    send_to_all_clients(server, ErrorFlag[error_id]);
}

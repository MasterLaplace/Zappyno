/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_error.c
*/

#include "../../include/send_package.h"

static char ErrorFlag[7][50] = {
    "ko",
    "ko Team is full",
    "ko Team not exists",
    "ko Join gui error",
    "ko Join ai error",
    "ko Map size error",
    "ko Error",
};

void send_error(t_client *client, int error_id) {
    send_to_client(client, ErrorFlag[error_id]);
}

void send_error_to_all(t_client *clients, int error_id) {
    send_to_all_clients(clients, ErrorFlag[error_id]);
}
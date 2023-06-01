/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_ai.c
*/

#include "../../../include/send_package.h"

void send_join_ai(t_server *server)
{
    send_to_client(server, "WELCOME");
}

void send_join_ai_to_all(t_server *server)
{
    send_to_all_clients(server, "WELCOME");
}
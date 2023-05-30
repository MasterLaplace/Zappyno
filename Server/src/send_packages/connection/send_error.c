/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** send_join_error.c
*/

#include "../../../include/send_package.h"

/*
 * struct PACKED Error {
 *    uint8_t command_id;
 * } Error;
 */

static Error set_join_error_struct(u_int8_t error_id) {
    Error error_ptr;
    error_ptr.flag = error_id;
    return error_ptr;
}

void send_error(t_client *client, u_int8_t error_id) {
    Package_t package;
    Error join_error = set_join_error_struct(error_id);
    package.command_id = ERROR;
    package.size = htons(sizeof(Error));
    send_to_client(client, &package, &join_error, sizeof(Error));
}

void send_error_to_all(t_client *clients, u_int8_t error_id) {
    printf("Error: %d\n", error_id);
    Package_t package;
    Error join_error = set_join_error_struct(error_id);
    package.command_id = ERROR;
    package.size = htons(sizeof(Error));
    send_to_all_clients(clients, &package, &join_error, sizeof(Error));
}
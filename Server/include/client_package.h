/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** client_package.h
*/

#ifndef CLIENT_PACKAGE_H
#define CLIENT_PACKAGE_H

#define COMMAND_NOT_FOUND 0x0
#define ADDED_TO_TEAM 0x1
#define TEAM_IS_FULL 0x2
#define TEAM_EXISTS 0x3
#define JOIN_CHECK_IA 0x4
#define MAP_SIZE 0x5

#include <arpa/inet.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <stddef.h>


#define PACKED __attribute__((packed))

typedef struct s_client t_client;

typedef struct PACKED {
    uint8_t command_id;
    uint16_t size;
} Package_t;

typedef struct PACKED {
    uint8_t command_ok;
} CommandFound;

typedef struct PACKED {
    uint8_t avalaible;
} AddedToTeam;

typedef struct PACKED {
    uint8_t is_full;
} TeamIsFull;

typedef struct PACKED {
    uint8_t exists;
} TeamExists;

typedef struct PACKED {
    uint8_t is_ia;
} JoinCheckIA;

typedef struct PACKED {
    uint8_t x;
    uint8_t y;
} MapSize;

//Function for structures
AddedToTeam set_added_to_team_struct(bool avalaible);
void send_added_to_team(t_client *client, bool avalaible);
void send_added_to_team_to_all(t_client *clients, bool avalaible);
//
TeamIsFull set_team_is_full_struct(bool is_full);
void send_team_is_full(t_client *client, bool is_full);
void send_team_is_full_to_all(t_client *clients, bool is_full);
//
TeamExists set_team_exists_struct(bool exists);
void send_team_exists(t_client *client, bool exists);
void send_team_exists_to_all(t_client *clients, bool exists);
#endif //CLIENT_PACKAGE_H
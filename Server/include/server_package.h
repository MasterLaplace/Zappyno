/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** package.h
*/

#ifndef PACKAGE_H
    #define PACKAGE_H
    #define COMMAND_NOT_FOUND 0x1
    #define TEAM_IS_FULL 0x2
    #define TEAM_EXISTS 0x3
    #define JOIN_GUI 0x4
    #define JOIN_AI 0x5
    #define MAP_SIZE 0x6
    #define ERROR 0x7

#include <arpa/inet.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <stddef.h>


#define PACKED __attribute__((packed))

typedef struct s_client t_client;

// PACKAGE STRUCT
typedef struct PACKED {
    uint8_t command_id;
    uint16_t size;
} Package_t;

// CONNECTION PACKAGES
typedef struct PACKED {
    uint8_t avalaible;
} JoinGui;

typedef struct PACKED {
    uint8_t avalaible;
    char team_name[32];
} JoinAI;

// 0 : command_not_ok
// 1 : team_is_full
// 2 : team_not_exists
// 4 : join_gui_error
// 8 : join_ai_error
typedef struct PACKED {
    uint8_t flag;
} Error;


// GUI PACKAGES
typedef struct PACKED {
    uint8_t x;
    uint8_t y;
} MapSize;

#endif //PACKAGE_H
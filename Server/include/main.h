/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.h
*/

#ifndef MAIN_H
    #define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "params.h"
#include "client.h"
#include "game.h"

static const char HELP[] = "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n\n"
                           "\tport \tis the port number\n"
                           "\twidth \tis the width of the world\n"
                           "\theight \tis the height of the world"
                           "\tnameX \tis the name of the team X\n"
                           "\tclientsNb \tis the number of authorized clients per team\n"
                           "\tfreq \tis the reciprocal of time unit for execution of actions\n";

#endif /* !MAIN_H */
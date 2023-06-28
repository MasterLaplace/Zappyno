/*
** EPITECH PROJECT, 2023
** Zappyno
** File description:
** main.h
*/

#ifndef MAIN_H
    #define MAIN_H

    #include "server.h"

static const char
HELP[] = "USAGE: ./zappy_server -p port -x width -y height"
    " -n name1 name2 ... -c clientsNb -f freq\n\n"
    "\tport \tis the port number\n"
    "\twidth \tis the width of the world\n"
    "\theight \tis the height of the world"
    "\tnameX \tis the name of the team X\n"
    "\tclientsNb \tis the number of authorized "
    "clients per team\n"
    "\tfreq \tis the reciprocal of time unit"
    " for execution of actions\n";

int main(int ac, char **av);
void exit_malloc(void);
void exit_timer(void);

#endif /* !MAIN_H */

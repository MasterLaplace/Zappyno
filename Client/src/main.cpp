/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy-tristan.bros
** File description:
** main.cpp
*/

#include "main.hpp"

static const std::string HELP = "USAGE: ./zappy_ai -p port -n name -h machine\n\n"
                                "\tport \tis the port number\n"
                                "\tname \tis the name of the team\n"
                                "\tmachine \tis the name of the machine; localhost by default";

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help")) {
        std::cout << HELP << std::endl;
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}

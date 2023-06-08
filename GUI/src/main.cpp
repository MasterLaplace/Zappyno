/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** core
*/

#include "../includes/Core.hpp"

int main(const int ac, const char *av[])
{
    try {
        Core core(ac, av);
    } catch (std::exception &e) {
        std::cout << "\nMain:" << std::endl;
        std::cerr << "\tError: " << e.what() << std::endl;
        std::cerr << "\tAborting..." << std::endl;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

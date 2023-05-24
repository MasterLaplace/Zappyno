/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_
    #define	EXIT_ERROR	84	/* Failing exit status.  */
    #define FRAMERATE 60
    #include <iostream>
    #include <memory>
    #include <chrono>
    #include <SFML/Graphics.hpp>
    #include "Client.hpp"

class Core {
    public:
        Core(const int ac, const char *av[]);
        ~Core() { _window->close(); }

        void showUsage(std::ostream &output);
        bool parseArgs(const int ac, const char *av[]);
        void run();

    protected:
    private:
        std::unique_ptr<sf::RenderWindow> _window;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<T> &obj) {
    os << *obj;
    return os;
}
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::shared_ptr<T> &obj) {
    os << *obj;
    return os;
}

#endif /* !CORE_HPP_ */

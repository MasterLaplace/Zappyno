/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(const int ac, const char *av[])
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "-help")) {
        this->showUsage(std::cout);
        return;
    }
    if (!this->parseArgs(ac, av))
        throw std::invalid_argument("Core: Invalid arguments, run with -h or -help for more informations");
    _window = std::make_unique<sf::RenderWindow>();
    _window->create(sf::VideoMode(1280, 960, 32), "GUI");
    _window->setFramerateLimit(FRAMERATE);

    this->run();
}

void Core::showUsage(std::ostream &output)
{
    output << "Usage: ./zappy_ai -p port -h machine" << std::endl;
    output << "\tport\tis the port number" << std::endl;
    output << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

bool Core::parseArgs(const int ac, const char *av[])
{
    auto port = 0;
    auto machine = "localhost";
    (void) machine;

    if (ac < 3)
        return showUsage(std::cerr), false;
    try {
        if (std::string(av[1]) != "-p")
            throw std::invalid_argument("Error: args<" + std::string(av[1]) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
        port = atoi(av[2]);
        if (port > MAX_PORT || port < MIN_PORT)
            throw std::invalid_argument("Error: args<" + std::to_string(port) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
        if (ac == 5) {
            if (std::string(av[3]) != "-h")
                throw std::invalid_argument("Error: args<" + std::string(av[3]) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
            machine = av[4];
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return showUsage(std::cerr), false;
    }

    /* RUN */
    return true;
}

void Core::run()
{
    static std::chrono::steady_clock::time_point clock = std::chrono::steady_clock::now();
    std::cout << "Core: Running..." << std::endl;

    while (_window->isOpen()) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed_time = now - clock;

        sf::Event event;

        if (elapsed_time >= std::chrono::milliseconds(FRAMERATE)) {
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    _window->close();
            }
            _window->clear();
            _window->display();

            clock = std::chrono::steady_clock::now();
            elapsed_time -= std::chrono::milliseconds(FRAMERATE);
        }
    }
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Core
*/

#include "../../includes/Core.hpp"
#include "../../includes/SfSprite.hpp"
#include <algorithm>
#include <list>

Core::Core(const unsigned ac, const char *av[])
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "-help")) {
        this->showUsage(std::cout);
        return;
    }
    if (!this->parseArgs(ac, av))
        throw std::invalid_argument("Core: Invalid arguments, run with -h or -help for more informations");
    _client = std::make_shared<Manager::Client>("127.0.0.1", std::stoi(av[2]));
    _window = std::make_shared<sf::RenderWindow>();
    _window->create(sf::VideoMode(WIN_X, WIN_Y), "GUI", sf::Style::Default);
    _window->setFramerateLimit(_client->getFramerate());
    _window->setVerticalSyncEnabled(true);

    /* LOAD SCENES */
    _scene = _sceneManager.create_scene<sf::RenderWindow, Sf_sprite::SfSprite>(GUI::SceneManager::MENU, _window);

    /* RUN */
    this->run();
}

void Core::run()
{
    std::cout << "Core: Running..." << std::endl;
    sf::Event event;
    std::string message;

    while (_window->isOpen()) {

        try {
            if ((message = _client->receiveFromServer()) != "") {
                std::cout << "Message received: " << message;
            }
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }


        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                _window->close();
        }

        _window->clear();
        // get the mouse position in the window
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*_window);
        Math::Vector mousePos = {double(pixelPos.x), double(pixelPos.y)};

        if (event.type == sf::Event::KeyReleased || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _scene->updateScene(mousePos, event.key.code, sf::Mouse::isButtonPressed(sf::Mouse::Left));
        } else {
            _scene->updateScene(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }
        _sceneManager.switchScene<sf::RenderWindow, Sf_sprite::SfSprite>(_window, _scene);
        _scene->drawScene<sf::RenderWindow>(*_window);

        _window->display();

    }
}

void Core::showUsage(std::ostream &output)
{
    output << "Usage: ./zappy_ai -p port -h machine" << std::endl;
    output << "\tport\tis the port number" << std::endl;
    output << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

bool Core::parseArgs(const unsigned ac, const char *av[])
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

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_
    #define	EXIT_ERROR	84	/* Failing exit status.  */
    #include "Protocol.hpp"
    #include "SfTransition.hpp"
    #include "Perlin.hpp"
    #include "Camera.hpp"
    #include "Scene.hpp"

class Core {
    public:
        Core(const unsigned ac, const char *av[]);
        ~Core() { if (_window && _window->isOpen()) _window->close(); }

        void showUsage(std::ostream &output);
        bool parseArgs(const unsigned ac, const char *av[]);
        void run();

    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;
        Engine::Camera camera;
        Sf_transition::Transition star = Sf_transition::Transition(Sf_transition::Transition::TransitionType::STARFIELD, std::numeric_limits<int>::max());
        Engine::Mesh map;
        Engine::Mesh cube;
        std::shared_ptr<GUI::Scene> _scene;
        GUI::SceneManager _sceneManager;
        std::shared_ptr<Manager::Protocol> _protocol;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::unique_ptr<T> &obj) { return os << *obj; }
template<typename T>
std::ostream &operator<<(std::ostream &os, const std::shared_ptr<T> &obj) { return os << *obj; }

#endif /* !CORE_HPP_ */

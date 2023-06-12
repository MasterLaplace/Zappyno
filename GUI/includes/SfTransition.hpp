/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SFML Transition Utils Library
*/

#ifndef SF_TRANSITION_HPP_
    #define SF_TRANSITION_HPP_
    #define WIN_X 1920
    #define WIN_Y 1080
    #define RANDINT(min, max) (rand() % (max - min + 1) + min)
    #include <random>
    #include <chrono>
    #include "SfPrimitive.hpp"

/**
 * @brief Star class
 *
 * @namespace Sf_transition
 * @example in SFML:
 * Sf_transition::Transition star = Sf_transition::Transition(Sf_transition::Transition::TransitionType::STARFIELD, 5000);
 * while (_window.isOpen()) {
 *      if (!star.isFinished())
 *          star.DoTransition(window);
 * }
 */
namespace Sf_transition {
    template<typename T, typename U, typename V>
    inline U map(T value, T start1, T end1, U start2, U end2);

    class Star {
        public:
            Star();

            void update(int speed);

            void show(sf::RenderWindow &_window);

        private:
            float _x;
            float _y;
            float _z;
            float _pz;
    };

    class Transition {
        public: /* ENUMS */
            enum TransitionType {
                FADE,
                SLIDE,
                STARFIELD
            };

        public: /* METHODS */
            Transition(TransitionType type, int timeout = 10000);
            ~Transition();

            bool isFinished();

            void reset(TransitionType type, int timeout = 10000);

            void DoTransition(sf::RenderWindow &_window);

        public: /* VARIABLES */
            TransitionType _type;
            int _timeout;
            std::chrono::time_point<std::chrono::high_resolution_clock> _start;
            Star *_stars;
    };
} // namespace Sf_transition

#endif /* !SF_TRANSITION_HPP_ */

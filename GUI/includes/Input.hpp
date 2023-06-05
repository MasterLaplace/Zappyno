/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Input
*/

#ifndef INPUT_HPP_
    #define INPUT_HPP_
    #include "Vector.hpp"
    #include "SfText.hpp"

/**
 * @brief Input class
 *
 * @namespace Interface
 * @example in SFML:
 * auto tt = Sf_text::Text_s("", {0, 0}, Sf_text::createFont("GUI/assets/OpenSans-ExtraBoldItalic.ttf"), sf::Color::Red);
 * Interface::Input _input = Interface::Input(Math::Vector(0, 0), Math::Vector(100, 100), 20, tt);
 * while (_window.isOpen()) {
 *      _input.updateState(mousePos, event.key.code, sf::Mouse::isButtonPressed(sf::Mouse::Left));
 *      _input.drawInput<sf::RenderWindow>(window);
 * }
 */
namespace Interface {
    class Input {
        public:
            enum State {
                IDLE,
                CLICKED
            };
        public:
            Input() = default;
            Input(Math::Vector pos, Math::Vector size, unsigned limit, Sf_text::Text_s &sfText) {
                _pos = pos;
                _size = size;
                this->limit = limit;
                _sfText = sfText;
            }
            ~Input() = default;

            void updateState(const Math::Vector &mousePos, int key, const bool &mousePressed = false);

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setSize(const Math::Vector &size) { _size = size; }
            void setLimit(const unsigned &limit) { this->limit = limit; }

            std::string getText() const { return _text; }
            Math::Vector getPos() const { return _pos; }
            Math::Vector getSize() const { return _size; }
            unsigned getState() const { return _state; }

            template<typename T>
            void drawInput(T &window) {
                _sfText.str = _text;
                Sf_text::DrawText(window, _sfText);
            }

        protected:
        private:
            std::string _text;
            Math::Vector _pos;
            Math::Vector _size;
            unsigned limit = 0;
            State _state = IDLE;
            Sf_text::Text_s _sfText;
    };
} // namespace Interface

#endif /* !INPUT_HPP_ */

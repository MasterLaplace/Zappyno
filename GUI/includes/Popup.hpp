/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Popup
*/

#ifndef POPUP_HPP_
    #define POPUP_HPP_
    #include "SfText.hpp"
    #include "ISprite.hpp"
    #include <chrono>
    #include <memory>

/**
 * @brief Popup class is used to create a popup
 *
 * @namespace Interface
 * @example in SFML:
 * Interface::Popup popup = Interface::Popup(std::make_shared<Sprite>(window, "GUI/assets/Popup.png", {0, 0}, {1, 1}), "Hello World");
 * while (_window.isOpen()) {
 *      popup.animate(sf::Mouse::getPosition(_window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
 *      popup.drawPopup();
 * }
 */
namespace Interface {
    class Popup {
        public:
            enum State {
                POP = 1000,
                FADE = 2500,
                END = 3000
            };
        public:
            Popup(std::shared_ptr<ISprite> sprite, double original_x, std::string text = "An egg has been cracked, time to eat!");
            ~Popup() = default;

            void setPos(const Math::Vector &pos) { _pos = pos; }

            Math::Vector getPos() const { return _pos; }
            State getState() const { return _state; }

            /**
             * @brief updateState is used to update the state of the popup (POP, FADE, END)
             *
             * @param mousePos  mouse position
             * @param mousePressed  is the mouse pressed
             */
            void updatePopup(const Math::Vector &mousePos, const bool &mousePressed);

            template<typename T>
            void drawPopup(T &window) {
                _sprite->drawSprite();
                Sf_text::DrawText(window, _sfText);
            }

        protected:
        private:
            Math::Vector _pos;
            std::chrono::time_point<std::chrono::high_resolution_clock> _start;
            std::shared_ptr<ISprite> _sprite;
            Sf_text::Text_s _sfText;
            State _state = POP;
            double originalX;
    };
}

#endif /* !POPUP_HPP_ */

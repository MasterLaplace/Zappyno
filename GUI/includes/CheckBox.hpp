/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** CheckBox
*/

#ifndef CHECKBOX_HPP_
    #define CHECKBOX_HPP_
    #include "ISprite.hpp"
    #include "Button.hpp"
    #include <chrono>
    #include <memory>

/**
 * @brief Button class
 *
 * @namespace Interface
 * @example in SFML:
 * Interface::Button button = Interface::Button(std::make_shared<Sprite>(window, "GUI/assets/button.png", {0, 0}, {1, 1}));
 * auto sprite = button.getSprite();
 * sprite->setOffset(Math::Vector(100, 100));
 * sprite->setMaxOffsetX(1);
 * button.setCallback(Interface::CALLBACK::EXIT);
 * while (_window.isOpen()) {
 *      button.animate(sf::Mouse::getPosition(_window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
 *      button.drawButton();
 * }
 */
namespace Interface {
    class Checkbox {
        public:
            enum State {
                IDLE,
                HOVER,
                CLICKED,
                RELEASED
            };
        public:
            Checkbox() = default;
            Checkbox(std::shared_ptr<ISprite> sprite) {
                _sprite = sprite;
                _pos = sprite->getPos();
                _size = sprite->getSize();
                _scale = sprite->getScale();
            }
            ~Checkbox() = default;

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setSize(const Math::Vector &size) { _size = size; }
            void setScale(const Math::Vector &scale) { _scale = scale; }
            void setCallback(const CALLBACK &callback) { _callback = callback; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            CALLBACK getCallback() const { return _callback; }
            State getState() const { return _state; }
            void updateState(const Math::Vector &mousePos, const bool &mousePressed = false);
            void animate(const Math::Vector &mousePos, const bool &mousePressed = false);
            void animate_checkbox(const Math::Vector &mousePos, const bool &mousePressed = false);
            void drawCheckbox() const { _sprite->drawSprite(); }

        protected:
        private:
            Math::Vector _pos;
            Math::Vector _size;
            Math::Vector _scale;
            std::shared_ptr<ISprite> _sprite;
            State _state = IDLE;
            CALLBACK _callback = NONE;
            bool ischecked = false;
    };
} // namespace Interface

#endif /* !CHECKBOX_HPP_ */

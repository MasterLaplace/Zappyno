/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_
    #include "ISprite.hpp"
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
    enum CALLBACK {
        NONE = -1,
        GOTO_CREATE,
        GOTO_GAME,
        GOTO_SETTING,
        GOTO_SETTING_PAUSE,
        GOTO_CREDIT,
        GOTO_RESULT,
        GOTO_MENU,
        RESIZE,
        VR,
        EXIT,
        MUTE_SOUND,
        OPEN_INVENTORY_USER,
        OPEN_INVENTORY_CASE,
        OPEN_PAUSE,
        FULL_SCREEN,
        FINAL
    };
    class Button {
        public:
            enum State {
                IDLE,
                HOVER,
                CLICKED,
                RELEASED
            };
        public:
            Button() = default;
            Button(std::shared_ptr<ISprite> sprite) {
                _sprite = sprite;
                _pos = sprite->getPos();
                _size = sprite->getSize();
                _scale = sprite->getScale();
            }
            ~Button() = default;

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setSize(const Math::Vector &size) { _size = size; }
            void setScale(const Math::Vector &scale) { _scale = scale; }
            void setState(const State &state) { _state = state; }
            void setCallback(const CALLBACK &callback) { _callback = callback; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            CALLBACK getCallback() const { return _callback; }
            State getState() const { return _state; }
            void updateState(const Math::Vector &mousePos, const bool &mousePressed = false);
            void animate(const Math::Vector &mousePos, const bool &mousePressed = false);
            void drawButton() const { _sprite->drawSprite(); }

        protected:
        private:
            Math::Vector _pos;
            Math::Vector _size;
            Math::Vector _scale;
            std::shared_ptr<ISprite> _sprite;
            State _state = IDLE;
            CALLBACK _callback = NONE;
    };
} // namespace Interface

#endif /* !BUTTON_HPP_ */

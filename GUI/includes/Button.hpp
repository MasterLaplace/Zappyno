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

namespace Interface {
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
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
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
    };
} // namespace Interface

#endif /* !BUTTON_HPP_ */

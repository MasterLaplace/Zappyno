/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Button
*/

#include "../../includes/Button.hpp"

namespace Interface {
    void Button::updateState(const Math::Vector &mousePos, const bool &mousePressed) {
        auto size = _sprite->getSize();
        if (mousePos.x() >= _pos.x() && mousePos.x() <= _pos.x() + size.x() &&
            mousePos.y() >= _pos.y() && mousePos.y() <= _pos.y() + size.y()) {
            if (_state == IDLE)
                _state = HOVER;
            if (_state == CLICKED)
                _state = RELEASED;
            if (mousePressed)
                _state = CLICKED;
        } else {
            if (!mousePressed || _state == HOVER)
                _state = IDLE;
        }
    }

    void Button::animate(const Math::Vector &mousePos, const bool &mousePressed) {
        updateState(mousePos, mousePressed);
        _sprite->animate(_state);
    }
} // namespace Interface

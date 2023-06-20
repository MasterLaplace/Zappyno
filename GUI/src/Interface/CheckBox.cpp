/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** CheckBox
*/

#include "../../includes/CheckBox.hpp"

namespace Interface {
    void Checkbox::updateState(const Math::Vector &mousePos, const bool &mousePressed) {
        auto size = _sprite->getSize();
        if (_state == RELEASED)
            _state = IDLE;
        if (mousePos.x() >= _pos.x() && mousePos.x() <= _pos.x() + size.x() &&
            mousePos.y() >= _pos.y() && mousePos.y() <= _pos.y() + size.y()) {
            if (_state == IDLE)
                _state = HOVER;
            if (_state == CLICKED && !mousePressed) {
                _state = RELEASED;
                ischecked = !ischecked;
            }
            if (mousePressed)
                _state = CLICKED;
        } else {
            _state = IDLE;
        }
    }

    void Checkbox::animate_checkbox(const Math::Vector &mousePos, const bool &mousePressed) {
        updateState(mousePos, mousePressed);
        _sprite->animate_checkbox(ischecked, _state);
    }
} // namespace Interface

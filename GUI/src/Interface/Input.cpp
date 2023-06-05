/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Input
*/

#include "../../includes/Input.hpp"

namespace Interface {
    void Input::updateState(const Math::Vector &mousePos, int key, const bool &mousePressed) {
        if (mousePos.x() >= _pos.x() && mousePos.x() <= _pos.x() + _size.x() && mousePos.y() >= _pos.y() && mousePos.y() <= _pos.y() + _size.y()) {
            if (mousePressed) {
                _state = CLICKED;
                return;
            }
        } else if (mousePressed)
            _state = IDLE;
        if (_state == CLICKED && key == 59 && _text.size() > 0)
            _text.pop_back();
        if (_text.size() >= limit)
            return;
        if (_state == CLICKED && key >= 0 && key <= 25)
            _text += char(key + 65);
        if (_state == CLICKED && key == 57)
            _text += ' ';
        if (_state == CLICKED && key == 50)
            _text += '.';
        if (_state == CLICKED && ((key >= 26 && key <= 35) || (key >= 75 && key <= 84)))
            _text += char(key - ((key >= 75)?75:26) + '0');
    }
}

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Panel
*/

#include "../../includes/Panel.hpp"

namespace Interface {
    void Panel::updatePanel(const Math::Vector &mousePos, const bool &mousePressed) {
        for (auto &button : _buttons)
            button.animate(mousePos, mousePressed);
        for (auto &checkbox : _checkboxs)
            checkbox.animate_checkbox(mousePos, mousePressed);
        for (auto &bar : _bars)
            bar.updateState();
        if (!_sprite) return;
        auto size = _sprite->getSize();
        if (_callback == OPEN_INVENTORY_USER && mousePressed &&
            ((mousePos.x() <= _pos.x() || mousePos.x() >= _pos.x() + size.x()) ||
            (mousePos.y() <= _pos.y() || mousePos.y() >= _pos.y() + size.y())))
            _callback = NONE;
        if (_callback == OPEN_INVENTORY_CASE && mousePressed &&
            ((mousePos.x() <= _pos.x() || mousePos.x() >= _pos.x() + size.x()) ||
            (mousePos.y() <= _pos.y() || mousePos.y() >= _pos.y() + size.y())))
            _callback = NONE;
    }

    void Panel::updatePanel(const Math::Vector &mousePos, int key, const bool &mousePressed) {
        for (auto &button : _buttons)
            button.animate(mousePos, mousePressed);
        for (auto &checkbox : _checkboxs)
            checkbox.animate_checkbox(mousePos, mousePressed);
        for (auto &input : _inputs)
            input.updateState(mousePos, key, mousePressed);
        for (auto &bar : _bars)
            bar.updateState();
        if (!_sprite) return;
        auto size = _sprite->getSize();
        if (_callback == OPEN_INVENTORY_USER && mousePressed &&
            ((mousePos.x() <= _pos.x() || mousePos.x() >= _pos.x() + size.x()) ||
            (mousePos.y() <= _pos.y() || mousePos.y() >= _pos.y() + size.y())))
            _callback = NONE;
        if (_callback == OPEN_INVENTORY_CASE && mousePressed &&
            ((mousePos.x() <= _pos.x() || mousePos.x() >= _pos.x() + size.x()) ||
            (mousePos.y() <= _pos.y() || mousePos.y() >= _pos.y() + size.y())))
            _callback = NONE;
    }

    void Panel::setUserData(std::vector<unsigned> data) {
        _text_user->operator[](0).setText(std::to_string(data[0]));
        _text_user->operator[](1).setText(std::to_string(data[1]));
        _text_user->operator[](2).setText(std::to_string(data[2]));
        _text_user->operator[](3).setText(std::to_string(data[3]));
        _text_user->operator[](4).setText(std::to_string(data[4]));
        _text_user->operator[](5).setText(std::to_string(data[5]));
        _text_user->operator[](6).setText(std::to_string(data[6]));
    }

    void Panel::setCaseData(std::vector<unsigned> data) {
        _text_case->operator[](0).setText(std::to_string(data[0]));
        _text_case->operator[](1).setText(std::to_string(data[1]));
        _text_case->operator[](2).setText(std::to_string(data[2]));
        _text_case->operator[](3).setText(std::to_string(data[3]));
        _text_case->operator[](4).setText(std::to_string(data[4]));
        _text_case->operator[](5).setText(std::to_string(data[5]));
        _text_case->operator[](6).setText(std::to_string(data[6]));
    }

    std::vector<CALLBACK> Panel::getCallback() {
        std::vector<CALLBACK> callback;
        for (auto &button : _buttons)
            if (button.getState() == Interface::Button::RELEASED)
                callback.push_back(button.getCallback());
        for (auto &checkbox : _checkboxs)
            if (checkbox.getState() == Interface::Checkbox::RELEASED)
                callback.push_back(checkbox.getCallback());
        return callback;
    }
} // namespace Interface

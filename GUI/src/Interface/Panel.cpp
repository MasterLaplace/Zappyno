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
        for (auto &bar : _bars)
            bar.updateState();
    }

    void Panel::updatePanel(const Math::Vector &mousePos, int key, const bool &mousePressed) {
        for (auto &button : _buttons)
            button.animate(mousePos, mousePressed);
        for (auto &input : _inputs)
            input.updateState(mousePos, key, mousePressed);
        for (auto &bar : _bars)
            bar.updateState();
    }

    std::vector<CALLBACK> Panel::getCallback() {
        std::vector<CALLBACK> callback;
        for (auto &button : _buttons)
            if (button.getState() == Interface::Button::RELEASED)
                callback.push_back(button.getCallback());
        return callback;
    }
} // namespace Interface

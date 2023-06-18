/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Popup
*/

#include "../../includes/Popup.hpp"

namespace Interface {
    Popup::Popup(std::shared_ptr<ISprite> sprite, std::string text) {
        _pos = sprite->getPos();
        _sprite = sprite;
        _sfText = Sf_text::Text_s(text, {_pos.x(), _pos.y()}, Sf_text::createFont("GUI/assets/OpenSans-ExtraBoldItalic.ttf"), sf::Color::Red);
        _start = std::chrono::high_resolution_clock::now();
    }

    void Popup::updateState(const Math::Vector &mousePos, const bool &mousePressed) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);

        // I have 3 states: POP, FADE, END (and I can't go back once I've passed the END state)
        // POP: the popup appears and moves in 1 second (from pos to pos - 100)
        // FADE: the popup disappears in 2 seconds (from 255 to 0)
        // END: the popup is completely transparent and doesn't move anymore (it's dead)
        // so if I'm in POP and I've exceeded 1 second, I go to FADE (and I reset the timer)
        // if I'm in FADE and I've exceeded 2 seconds, I go to END
        // if I click on the popup, I go directly to END
        // if I'm in END, I do nothing
        if (mousePos.x() >= _pos.x() && mousePos.x() <= _pos.x() + _sprite->getSize().x()
            && mousePos.y() >= _pos.y() && mousePos.y() <= _pos.y() + _sprite->getSize().y()
            && mousePressed) {
            _state = END;
            return;
        } else if (_state == POP && elapsed.count() > POP) {
            _state = FADE;
            _start = std::chrono::high_resolution_clock::now();
        } else if (_state == FADE && elapsed.count() > FADE) {
            _state = END;
            return;
        }
        if (_state == POP) { // 1 second to translate from 0 to 100
            _sprite->setPos(_pos + Math::Vector(100 * (elapsed.count() / 1000.0), _sprite->getPos().y()));
        } else if (_state == FADE) { // 2 seconds to be fully transparent
            _sprite->setTransparency(255 - ((elapsed.count() / 2000.0) * 255));
        }
    }
} // namespace Interface

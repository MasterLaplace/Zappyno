/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Popup
*/

#include "../../includes/Popup.hpp"

namespace Interface {
Popup::Popup(std::shared_ptr<ISprite> sprite, double original_x, std::string text) {
    _pos = sprite->getPos();
    originalX = original_x;
    _sprite = sprite;
    _sfText = Sf_text::Text_s(text, {float(_pos.x()), float(_pos.y())}, Sf_text::createFont("GUI/assets/OpenSans-ExtraBoldItalic.ttf"), sf::Color::Red);
    _start = std::chrono::high_resolution_clock::now();
}

void Popup::updatePopup(const Math::Vector &mousePos, const bool &mousePressed) {
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);

    // I have 3 states: POP(1000), FADE(2500), END (and I can't go back once I've passed the END state)
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
    if (_state == POP) { // 1 second to translate from 0 to sprite size x
        double ratio = double(elapsed.count()) / double(POP);
        _sprite->setPos({originalX - (_sprite->getSize().x() * ratio), _pos.y()});
        _sfText.pos = sf::Vector2f(_sprite->getPos().x() + 10 , _pos.y() + _sprite->getSize().y() / 2 - 10);
        _pos = _sprite->getPos();
    } else if (_state == FADE) { // 2.5 seconds to be fully transparent
        double ratio = double(elapsed.count()) / double(FADE);
        _sprite->setTransparency(255 - (ratio * 255));
        _sfText.color.a = 255 - (ratio * 255);
    }
}
} // namespace Interface

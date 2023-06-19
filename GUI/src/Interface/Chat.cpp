/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Chat
*/

#include "../../includes/Chat.hpp"

namespace Interface {
    void Chat::addMessage(const std::string &message, const sf::Color &color) {
        Sf_text::Text_s text;
        text.str = message;
        text.color = color;
        text.size = 20;
        text.font = _font;
        text.pos = sf::Vector2f(_pos.x(), _pos.y() + (_chat.size() * 20));
        _chat.push_back(text);
        if (_chat.size() > limit)
            _chat.pop_front();
    }
} // namespace Interface

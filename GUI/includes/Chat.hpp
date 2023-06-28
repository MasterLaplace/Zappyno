/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Chat
*/

#ifndef CHAT_HPP_
    #define CHAT_HPP_
    #include "Vector.hpp"
    #include "SfText.hpp"
    #include <deque>

namespace Interface {
    class Chat {
        public:
            Chat(const std::string &font) {
                _font = Sf_text::createFont(font);
                _chat.emplace_back(Sf_text::Text_s("Welcome to the server !", sf::Vector2f(0, 0), _font, sf::Color::Red, 20));
            }
            Chat(const Chat &other) {
                _chat = other._chat;
                _pos = other._pos;
                _font = other._font;
            }
            ~Chat() = default;

            void addMessage(const std::string &message, const sf::Color &color = sf::Color::Black);

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setLimit(unsigned limit) { this->limit = limit; }

            template<typename Win>
            void drawChat(Win &window) {
                for (auto &text : _chat) {
                    Sf_text::DrawText(window, text);
                }
            }

        protected:
        private:
            std::deque<Sf_text::Text_s> _chat;
            Math::Vector _pos;
            sf::Font _font;
            unsigned limit = 10;
    };
} // namespace Interface

#endif /* !CHAT_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_
    #include "Vector.hpp"
    #include "SfText.hpp"

namespace Interface {
    class Text {
        public:
            Text(const std::string &font) { 
                std::cout << "HELLO: " << font << std::endl;
                _text.font = Sf_text::createFont(font); }
            Text(const Text &other) = default;
            ~Text() = default;

            void setPos(const Math::Vector &pos) { _text.pos = sf::Vector2f(pos.x(), pos.y()); }

            std::string getText() const { return _text.str; }
            void setText(std::string text) { _text.str = text; }

            template<typename Win>
            void drawText(Win &window) {
                Sf_text::DrawText(window, _text);
            }

        protected:
        private:
            Sf_text::Text_s _text;
    };
} // namespace Interface

#endif /* !TEXT_HPP_ */

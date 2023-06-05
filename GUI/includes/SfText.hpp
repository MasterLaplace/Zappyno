/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SFML Text Utils Library
*/

#ifndef SF_TEXT_HPP_
    #define SF_TEXT_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>

namespace Sf_text {
    struct Text_s {
        sf::Font font;
        std::string str;
        sf::Vector2f pos;
        sf::Color color = sf::Color::White;
        int size = 24;

        Text_s(std::string str, sf::Vector2f pos, sf::Font font, sf::Color color = sf::Color::White, int size = 24) {
            this->font = font;
            this->str = str;
            this->pos = pos;
            this->color = color;
            this->size = size;
        }
        Text_s() = default;
    };

    sf::Font createFont(const std::string &pathname);
    void DrawText(sf::RenderWindow &window, Text_s &text);
} // namespace Sf_text

#endif /* !SF_TEXT_HPP_ */

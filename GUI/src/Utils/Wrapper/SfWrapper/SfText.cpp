/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SfText
*/

#include "../../../../includes/SfText.hpp"

namespace Sf_text {
    sf::Font createFont(const std::string &pathname) {
        sf::Font font;

        try {
            if (!font.loadFromFile(pathname)) {
                throw std::runtime_error("Font: Failed to open ftt file " + pathname + " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        return font;
    }

    void DrawText(sf::RenderWindow &window, Text_s &text)
    {
        sf::Text Sf_text;

        Sf_text.setFont(text.font);
        Sf_text.setString(text.str);
        Sf_text.setCharacterSize(text.size);
        Sf_text.setFillColor(sf::Color::Black);
        Sf_text.setPosition(text.pos);

        window.draw(Sf_text);
    }
} // namespace Sf_text

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** sfPrimitive
*/

#ifndef SFPRIMITIVE_HPP_
    #define SFPRIMITIVE_HPP_
    #include <SFML/Graphics.hpp>
    #include "Triangle.hpp"
    #include <iostream>
    #include <memory>

namespace Sf_primitive {

    //* LINE */
    struct Line_s {
        sf::Vector2f point1;
        sf::Vector2f point2;
        sf::Color color;

        Line_s() = default;
        Line_s(sf::Vector2f point1, sf::Vector2f point2, sf::Color color = sf::Color::White) {
            this->point1 = point1;
            this->point2 = point2;
            this->color = color;
        }
        void setTransparency(int transparency) { this->color.a = transparency; }
    };
    void drawLine(sf::RenderWindow &window, const Line_s &line);

} // namespace Sf_primitive

#endif /* !SFPRIMITIVE_HPP_ */

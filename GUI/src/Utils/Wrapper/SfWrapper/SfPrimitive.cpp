/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SfPrimitive
*/

#include "../../../../includes/SfPrimitive.hpp"

namespace Sf_primitive {

    void drawLine(sf::RenderWindow &window, const Line_s &line) {
        sf::Vertex vertices[] = {
            sf::Vertex(line.point1, line.color),
            sf::Vertex(line.point2, line.color)
        };
        window.draw(vertices, 2, sf::Lines);
    }

} // namespace Sf_primitive

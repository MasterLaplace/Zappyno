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

    void drawTriangleNotFill(sf::RenderWindow &window, const Triangle_s &triangle) {
        Line_s line1 = {triangle.point[0], triangle.point[1], triangle.color};
        Line_s line2 = {triangle.point[1], triangle.point[2], triangle.color};
        Line_s line3 = {triangle.point[2], triangle.point[0], triangle.color};
        drawLine(window, line1);
        drawLine(window, line2);
        drawLine(window, line3);
    }

    void drawTriangle(sf::RenderWindow &window, const Triangle_s &triangle) {
        sf::Vertex vertices[] = {
            sf::Vertex(triangle.point[0], triangle.color),
            sf::Vertex(triangle.point[1], triangle.color),
            sf::Vertex(triangle.point[2], triangle.color)
        };
        if (triangle.texture != nullptr) {
            vertices[0].texCoords = triangle.textureCoords[0];
            vertices[1].texCoords = triangle.textureCoords[1];
            vertices[2].texCoords = triangle.textureCoords[2];
            window.draw(vertices, 3, sf::Triangles, triangle.texture.get());
        } else
            window.draw(vertices, 3, sf::Triangles);
    }

    void drawRectangle(sf::RenderWindow &window, const Rectangle_s &rectangle) {
        sf::Vertex vertices[] = {
            sf::Vertex(rectangle.point[0], rectangle.color),
            sf::Vertex(rectangle.point[1], rectangle.color),
            sf::Vertex(rectangle.point[2], rectangle.color),
            sf::Vertex(rectangle.point[3], rectangle.color)
        };
        if (rectangle.texture != nullptr) {
            vertices[0].texCoords = rectangle.textureCoords[0];
            vertices[1].texCoords = rectangle.textureCoords[1];
            vertices[2].texCoords = rectangle.textureCoords[2];
            vertices[3].texCoords = rectangle.textureCoords[3];
            window.draw(vertices, 4, sf::Quads, rectangle.texture.get());
        } else
            window.draw(vertices, 4, sf::Quads);
    }

    void drawCircle(sf::RenderWindow &window, const Circle_s &circle) {
        sf::CircleShape shape(circle.radius);
        shape.setPosition(circle.center);
        shape.setFillColor(circle.color);
        window.draw(shape);
    }
} // namespace Sf_primitive

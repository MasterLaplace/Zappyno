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

    //* TRIANGLE */
    struct Triangle_s {
        sf::Vector2f point[3];
        sf::Vector2f textureCoords[3];
        sf::Color color;
        std::shared_ptr<sf::Texture> texture = nullptr;

        Triangle_s() = default;
        ~Triangle_s() = default;
        sf::Vector2f operator=(const Math::Vector point) {
            return sf::Vector2f(point.x(), point.y());
        }
        Triangle_s(const Engine::Triangle &tri) {
            this->point[0] = sf::Vector2f(tri[0].x(), tri[0].y());
            this->point[1] = sf::Vector2f(tri[1].x(), tri[1].y());
            this->point[2] = sf::Vector2f(tri[2].x(), tri[2].y());
            this->color = sf::Color(255 * tri.GetDp(), 255 * tri.GetDp(), 255 * tri.GetDp());
        }
        Triangle_s(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Color color = sf::Color::White) {
            this->point[0] = point1;
            this->point[1] = point2;
            this->point[2] = point3;
            this->color = color;
        }
        void setColor(sf::Color color) { this->color = color; }
        void setTransparency(int transparency) { this->color.a = transparency; }
        void setTexture(std::shared_ptr<sf::Texture> texture, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3) {
            this->texture = texture;
            this->textureCoords[0] = point1;
            this->textureCoords[1] = point2;
            this->textureCoords[2] = point3;
        }
        void setTexture(std::shared_ptr<sf::Texture> texture, const Engine::Triangle &tri) {
            this->texture = texture;
            auto point1 = tri.GetTexCoord(0);
            auto point2 = tri.GetTexCoord(1);
            auto point3 = tri.GetTexCoord(2);
            this->textureCoords[0] = sf::Vector2f(point1.x(), point1.y());
            this->textureCoords[1] = sf::Vector2f(point2.x(), point2.y());
            this->textureCoords[2] = sf::Vector2f(point3.x(), point3.y());
        }
    };
    void drawTriangleNotFill(sf::RenderWindow &window, const Triangle_s &triangle);
    void drawTriangle(sf::RenderWindow &window, const Triangle_s &triangle);

    //* RECTANGLE */
    struct Rectangle_s {
        sf::Vector2f point[4];
        sf::Vector2f textureCoords[4];
        sf::Color color;
        std::shared_ptr<sf::Texture> texture = nullptr;

        Rectangle_s() = default;
        ~Rectangle_s() = default;
        Rectangle_s(sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4, sf::Color color = sf::Color::White) {
            this->point[0] = point1;
            this->point[1] = point2;
            this->point[2] = point3;
            this->point[3] = point4;
            this->color = color;
        }
        void setTransparency(int transparency) { this->color.a = transparency; }
        void setTexture(std::shared_ptr<sf::Texture> texture, sf::Vector2f point1, sf::Vector2f point2, sf::Vector2f point3, sf::Vector2f point4) {
            this->texture = texture;
            this->textureCoords[0] = point1;
            this->textureCoords[1] = point2;
            this->textureCoords[2] = point3;
            this->textureCoords[3] = point4;
        }
    };
    void drawRectangle(sf::RenderWindow &window, const Rectangle_s &rectangle);

    //* CIRCLE */
    struct Circle_s {
        sf::Vector2f center;
        float radius;
        sf::Color color;

        Circle_s() = default;
        Circle_s(sf::Vector2f center, float radius, sf::Color color = sf::Color::White) {
            this->center = center;
            this->radius = radius;
            this->color = color;
        }
        void setTransparency(int transparency) { this->color.a = transparency; }
    };
    void drawCircle(sf::RenderWindow &window, const Circle_s &circle);
} // namespace Sf_primitive

#endif /* !SFPRIMITIVE_HPP_ */

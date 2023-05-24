/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace Engine {
    Triangle::Triangle() {
        _vertex[0] = Math::Vector();
        _vertex[1] = Math::Vector();
        _vertex[2] = Math::Vector();
    }
    Triangle::Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2) {
        _vertex[0] = v0;
        _vertex[1] = v1;
        _vertex[2] = v2;
    }
    Triangle::Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2,
                const Math::Vector &t0, const Math::Vector &t1, const Math::Vector &t2) {
        _vertex[0] = v0;
        _vertex[1] = v1;
        _vertex[2] = v2;
        _tex_coords[0] = t0;
        _tex_coords[1] = t1;
        _tex_coords[2] = t2;
    }
    Triangle::Triangle(const Triangle &triangle) {
        _vertex[0] = triangle[0];
        _vertex[1] = triangle[1];
        _vertex[2] = triangle[2];
        _tex_coords[0] = triangle._tex_coords[0];
        _tex_coords[1] = triangle._tex_coords[1];
        _tex_coords[2] = triangle._tex_coords[2];
    }

    Triangle &Triangle::operator=(const Triangle &triangle) {
        _vertex[0] = triangle[0];
        _vertex[1] = triangle[1];
        _vertex[2] = triangle[2];
        _tex_coords[0] = triangle._tex_coords[0];
        _tex_coords[1] = triangle._tex_coords[1];
        _tex_coords[2] = triangle._tex_coords[2];
        return *this;
    }

    bool Triangle::operator==(const Triangle &triangle) const {
        return _vertex[0] == triangle[0] && _vertex[1] == triangle[1] && _vertex[2] == triangle[2];
    }

    std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
        os << "Triangle: " << std::endl;
        os << "\tVertex 0: " << triangle[0] << std::endl;
        os << "\tVertex 1: " << triangle[1] << std::endl;
        os << "\tVertex 2: " << triangle[2] << std::endl;
        return os;
    }
}

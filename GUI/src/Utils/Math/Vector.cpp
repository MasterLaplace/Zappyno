/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Math Library
*/

#include "../../../includes/Vector.hpp"
#include <cstdlib>

namespace Math {
    Vector operator+(Vector lhs, const Vector &rhs) {
        lhs += rhs;
        return lhs;
    };

    Vector operator*(Vector lhs, const Vector &rhs) {
        lhs *= rhs;
        return lhs;
    };

    Vector operator/(Vector lhs, const Vector &rhs) {
        lhs /= rhs;
        return lhs;
    };

    Vector operator/(Vector vec, double scalar) {
        vec /= scalar;
        return vec;
    };
    Vector operator-(const Vector lhs, const Vector rhs) {
        return Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
    };

    Vector operator*(const double &scalar, const Vector &vec) {
        return Vector(scalar * vec.x(), scalar * vec.y(), scalar * vec.z());
    };

    Vector operator*(const Vector &vec, const double &scalar) {
        return Vector(vec.x() * scalar, vec.y() * scalar, vec.z() * scalar);
    };

    double dot(const Vector &lhs, const Vector &rhs) {
        return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
    };

    Vector cross(const Vector &lhs, const Vector &rhs) {
        return Vector(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                            lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                            lhs.x() * rhs.y() - lhs.y() * rhs.x());
    };

    double Vector::length() const {
        return sqrt(length_squared());
    };

    double Vector::length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    };

    Vector Vector::normalise() const {
        return *this / length();
    };

    double radians(double degrees) { return degrees * M_PI / 180.0; };

    std::ostream &operator<<(std::ostream &os, const Vector &vector) {
        os << "Vector content:" << std::endl;
        try {
            os << "\tx: " << vector.x() << " y: " << vector.y() << " z: " << vector.z() << " w: " << vector.w() << std::endl;
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        return os;
    }
}

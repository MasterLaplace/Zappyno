/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Math Library
*/

#ifndef MATH_HPP_
    #define MATH_HPP_
    #include "cmath"
    #include <string>
    #include <iostream>
    #include <vector>

namespace Math {
    class Vector {
        public:
            Vector() : e{0, 0, 0, 1} {}
            Vector(double e0, double e1 = 0, double e2 = 0, double e3 = 1) : e{e0, e1, e2, e3} {}
            Vector(const std::string &str) {
                std::string::size_type sz;

                e[0] = std::stof(str, &sz);
                e[1] = std::stof(str.substr(sz));
                e[2] = std::stof(str.substr(sz));
                e[3] = 1;
            }
            Vector(const std::vector<std::string> &str) {
                e[0] = std::stof(str[0]);
                e[1] = std::stof(str[1]);
                e[2] = (str.size() > 2 ) ? std::stof(str[2]) : 0;
                e[3] = 1;
            }
            Vector(const Vector &vec) = default;
            ~Vector() = default;

            double x() const { return e[0]; }
            double y() const { return e[1]; }
            double z() const { return e[2]; }
            double w() const { return e[3]; }
            void x(double x) { e[0] = x; }
            void y(double y) { e[1] = y; }
            void z(double z) { e[2] = z; }
            void w(double w) { e[3] = w; }

            Vector &operator=(const Vector &vec) = default;
            template <typename T> // 3D to 2D
            T &operator=(const Math::Vector &vec) { return T(vec.x, vec.y); }
            template <typename T> // 3D to 2D
            Math::Vector operator=(const T &vec) { return Math::Vector(vec.x(), vec.y()); }
            bool operator==(const Vector &other) const { return (e[0] == other.e[0] && e[1] == other.e[1] && e[2] == other.e[2] && e[3] == other.e[3]); }
            Vector operator-() const { return Vector(-e[0], -e[1], -e[2], -e[3]); }
            double operator[](int i) const { return e[i]; }
            double &operator[](int i) { return e[i]; }

            Vector min(const Vector &other) const { return Vector(std::min(x(), other.x()), std::min(y(), other.y()), std::min(z(), other.z()), std::min(w(), other.w())); }
            Vector max(const Vector &other) const { return Vector(std::max(x(), other.x()), std::max(y(), other.y()), std::max(z(), other.z()), std::max(w(), other.w())); }

            Vector &operator+=(const Vector &v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            Vector &operator-=(const Vector &v) {
                e[0] -= v.e[0];
                e[1] -= v.e[1];
                e[2] -= v.e[2];
                return *this;
            }

            Vector &operator*=(const Vector &other) {
                e[0] *= other.e[0];
                e[1] *= other.e[1];
                e[2] *= other.e[2];
                e[3] *= other.e[3];
                return *this;
            }

            Vector &operator/=(const Vector &other) {
                e[0] /= other.e[0];
                e[1] /= other.e[1];
                e[2] /= other.e[2];
                e[3] /= other.e[3];
                return *this;
            }

            Vector &operator*=(const double t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                e[3] *= t;
                return *this;
            }

            double length_squared() const;
            double length() const;

            Vector cross(const Vector &other) const {
                return Vector(y() * other.z() - z() * other.y(),
                                z() * other.x() - x() * other.z(),
                                x() * other.y() - y() * other.x());
            }

            double dot(const Vector &other) const {
                return x() * other.x() + y() * other.y() + z() * other.z();
            }

            Vector normalise() const;

        public:
            double e[4];
    };

    Vector operator+(Vector lhs, const Vector &rhs);
    Vector operator*(Vector lhs, const Vector &rhs);
    Vector operator/(Vector lhs, const Vector &rhs);
    Vector operator/(Vector vec, double scalar);
    Vector operator-(const Vector lhs, const Vector rhs);
    Vector operator*(const double &scalar, const Vector &vec);
    Vector operator*(const Vector &vec, const double &scalar);
    Vector cross(const Vector &lhs, const Vector &rhs);
    double dot(const Vector &lhs, const Vector &rhs);
    std::ostream &operator<<(std::ostream &os, const Vector &vector);

    double radians(double degrees);
    template <typename T>
    inline T clamp(T x, T min, T max) { return x < min ? min : (x > max ? max : x); }

    using Rect = Vector;
} // namespace Math

#endif /* !MATH_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
    #define TRIANGLE_HPP_
    #include "Vector.hpp"

namespace Engine {
    class Triangle {
        public:
            Triangle();
            Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2);
            Triangle(const Math::Vector &v0, const Math::Vector &v1, const Math::Vector &v2,
                const Math::Vector &t0, const Math::Vector &t1, const Math::Vector &t2);
            Triangle(const Triangle &triangle);
            ~Triangle() = default;

            Triangle &operator=(const Triangle &triangle);
            bool operator==(const Triangle &triangle) const;
            template <typename T>
            Math::Vector &operator[](T index) { return _vertex[index]; }
            template <typename T>
            const Math::Vector &operator[](T index) const { return _vertex[index]; }
            void SetVertex(std::size_t index, const Math::Vector &v) { _vertex[index] = v; }

        protected:
        private:
            Math::Vector _vertex[3];
            Math::Vector _tex_coords[3] = {
                Math::Vector(0, 0),
                Math::Vector(0, 1),
                Math::Vector(1, 1)
            };
    };
    std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
}

#endif /* !TRIANGLE_HPP_ */

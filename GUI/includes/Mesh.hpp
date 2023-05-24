/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Mesh
*/

#ifndef MESH_HPP_
    #define MESH_HPP_
    #include "Triangle.hpp"
    #include <vector>
    #include <memory>

namespace Engine {
    class Mesh {
        public:
            Mesh() = default;
            ~Mesh() = default;

            void add(std::shared_ptr<Triangle> shape);
            double getTransparancy() const { return _transparancy; }
            void setTransparancy(const double transpary) { _transparancy = transpary; }

        protected:
        private:
            std::vector<std::shared_ptr<Triangle>> _shapes;
            double _transparancy;
    };
}

#endif /* !MESH_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Mesh
*/

#ifndef MESH_HPP_
    #define MESH_HPP_
    #include "Triangle.hpp"
    #include "Matrix.hpp"
    #include <vector>
    #include <memory>

namespace Engine {
    class Mesh {
        public:
            Mesh() = default;
            ~Mesh() = default;

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setRot(const Math::Vector &angle) { _angle = angle; }
            void setScale(const Math::Vector &scale) { _scale = scale; }

            Math::Vector getPos() const { return _pos; }
            Math::Vector getRot() const { return _angle; }
            Math::Vector getScale() const { return _scale; }

            void add(std::shared_ptr<Triangle> shape);
            std::vector<std::shared_ptr<Triangle>> &getShapes() { return _shapes; }
            double getTransparancy() const { return _transparancy; }
            void setTransparancy(const double transpary) { _transparancy = transpary; }

            void Transform(Math::Vector pos, Math::Vector angle, Math::Vector scale);
            Math::Matrix &getModelToWorld() { return _modelToWorld; }

            // take a pointer to a function that takes a window and a triangle struct type
            template <typename Win, typename T>
            void drawMesh(void (*draw)(Win &, const T &), Win &window) const {
                for (auto &shape : _shapes) {
                    T triangle(*shape);
                    shape->drawTriangle(draw, window, triangle);
                }
            }

        protected:
        private:
            std::vector<std::shared_ptr<Triangle>> _shapes;
            Math::Matrix _modelToWorld;
            double _transparancy;
            Math::Vector _pos;
            Math::Vector _angle;
            Math::Vector _scale;
    };
    std::ostream &operator<<(std::ostream &os, Mesh &mesh);
} // namespace Engine

#endif /* !MESH_HPP_ */

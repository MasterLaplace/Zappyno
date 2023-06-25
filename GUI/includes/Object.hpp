/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Object
*/

#ifndef OBJECT_HPP_
    #define OBJECT_HPP_
    #include "Mesh.hpp"
    #include "Button.hpp"

namespace GUI {
    class Object {
        public:
            Object() = default;
            ~Object() = default;

            void setPos(Math::Vector pos) { _pos = pos; }
            void setRot(Math::Vector rot) { _rot = rot; }
            void setScale(Math::Vector scale) { _scale = scale; }
            void setMesh(Engine::Mesh mesh) { _mesh = mesh; }
            void setButton(Interface::Button button) { _button = button; }

            Math::Vector getPos() { return _pos; }
            Math::Vector getRot() { return _rot; }
            Math::Vector getScale() { return _scale; }
            Engine::Mesh &getMesh() { return _mesh; }
            Interface::Button getButton() { return _button; }

        protected:
        private:
            Engine::Mesh _mesh;
            Interface::Button _button;
            Math::Vector _pos;
            Math::Vector _rot;
            Math::Vector _scale;
    };
} // namespace GUI

#endif /* !OBJECT_HPP_ */

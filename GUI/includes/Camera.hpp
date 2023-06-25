/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_
    #include "Matrix.hpp"

namespace Engine {
    class Camera {
        public:
            Camera();
            ~Camera();

            void setPos(const Math::Vector &pos) { _Pos = pos; }
            void setDir(const Math::Vector &dir) { _Dir = dir; }
            void setFawZ(const float faw) { fawZ = faw; }
            void setFawY(const float faw) { fawY = faw; }
            void setFawX(const float faw) { fawX = faw; }

            Math::Vector &getPos() { return _Pos; }
            Math::Vector &getDir() { return _Dir; }
            float getFawZ() const { return fawZ; }
            float getFawY() const { return fawY; }
            float getFawX() const { return fawX; }
            Math::Matrix &getWorldToView() { return _worldtoView; }
            Math::Vector getForward(const float &speed) { return Math::Vector(_Dir * speed); }

            void moveForward(const float &speed) {
                _Pos.operator[](0) += _Dir.x() * speed;
                _Pos.operator[](1) += _Dir.y() * speed;
                _Pos.operator[](2) += _Dir.z() * speed;
            }
            void moveRight(const Math::Vector &forward) { _Pos += forward; }
            void moveUp(const float &speed) { _Pos.operator[](2) += _Dir.y() * speed; }

            void Transform();

        protected:
        private:
            Math::Matrix _worldtoView;
            Math::Vector _Pos;
            Math::Vector _Dir;
            float fawZ = 0;
            float fawY = 0;
            float fawX = 0;
    };
} // namespace Engine

#endif /* !CAMERA_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Camera
*/

#include "../../includes/Camera.hpp"

namespace Engine {
    Camera::Camera() {}

    Camera::~Camera() {}

    void Camera::Transform()
    {
        // World to View (W2V)
        Math::Matrix Rotate;
        Math::Matrix RotateY;
        Math::Matrix RotateX;
        Math::Matrix RotateZ;
        Math::Vector Dir = {0, 0, 1, 1};
        Math::Vector Up = {0, 1, 0, 1};

        RotateX.SetRotateXMatrix(fawX);
        RotateY.SetRotateYMatrix(fawY);
        RotateZ.SetRotateZMatrix(fawZ);
        Rotate.Multiply(RotateX, RotateY);
        Rotate.Multiply(RotateZ, Rotate);
        Rotate.MultiplyVector(this->_Dir, Dir);
        Dir = this->_Pos + this->_Dir;
        _worldtoView.SetViewMatrix(this->_Pos, Dir, Up);
    }
} // namespace Engine

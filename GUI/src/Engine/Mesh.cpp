/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Mesh
*/

#include "../../includes/Mesh.hpp"

namespace Engine {
    void Mesh::add(std::shared_ptr<Triangle> shape) { _shapes.push_back(shape); }

    //* Mesh transformation */
    void Mesh::Transform(Math::Vector pos, Math::Vector angle, Math::Vector scale)
    {
        // Model to World (M2W)
        Math::Matrix Rotate;
        Math::Matrix RotateY;
        Math::Matrix RotateX;
        Math::Matrix RotateZ;
        Math::Matrix Translate;
        Math::Matrix Scale;

        // Rotation matrices : around the z-axis - around the y-axis - around the x-axis
        RotateX.SetRotateXMatrix(angle.x());
        RotateY.SetRotateYMatrix(angle.y());
        RotateZ.SetRotateZMatrix(angle.z());
        Rotate.Multiply(RotateX, RotateY);
        Rotate.Multiply(Rotate, RotateZ);
        // Translation matrix
        Translate.SetTranslateMatrix(pos.x(), pos.y(), pos.z());
        _modelToWorld.Multiply(Rotate, Translate);
        // Scaling matrix
        Scale.SetScaleMatrix(scale.x(), scale.y(), scale.z());
        _modelToWorld.Multiply(_modelToWorld, Scale);
    }

    std::ostream &operator<<(std::ostream &os, Mesh &mesh) {
        return os << "Mesh: " << mesh.getShapes().size() << " triangles" << std::endl;
    }
} // namespace Engine

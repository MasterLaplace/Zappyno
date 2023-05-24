/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Mesh
*/

#include "Mesh.hpp"

namespace Engine {
    void Mesh::add(std::shared_ptr<Triangle> shape) {
        _shapes.push_back(shape);
    }
}

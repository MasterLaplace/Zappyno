/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Pipeline
*/

#include "../../includes/Pipeline.hpp"

namespace Engine {
    void Pipeline::geometry_rendering(Mesh &mesh, std::shared_ptr<Triangle> tri, bool isVR) {
        Engine::Triangle triTransformed, triViewed, triProjected, triProjected2;

        //* Model to World (M2W) */
        auto ModeltoWorld = mesh.getModelToWorld();
        ModeltoWorld.MultiplyVector(triTransformed[0], tri->operator[](0));
        ModeltoWorld.MultiplyVector(triTransformed[1], tri->operator[](1));
        ModeltoWorld.MultiplyVector(triTransformed[2], tri->operator[](2));

        //* World to View (W2V) */
        //* Backface culling */
        Math::Vector Normal, Line1, Line2;
        Line1 = triTransformed[1] - triTransformed[0];
        Line2 = triTransformed[2] - triTransformed[0];

        Normal = Math::cross(Line1, Line2).normalise();
        Math::Vector CameraRay = (triTransformed[0] - _cam->getPos());
        // if (Math::dot(Normal, CameraRay) >= 0.0f)
        //     return;
        // if (Normal.z() >= 0.0f)
        //     return;

        // Illumination
        // Math::Vector LightDirection = {0.0f, 0.0f, -1.0f};
        // LightDirection.normalise();
        // triProjected.SetDp(Math::dot(Normal, LightDirection));
        // triProjected2.SetDp(Math::dot(Normal, LightDirection));

        //* World to View (W2V) */
        auto WorldToView = _cam->getWorldToView();
        WorldToView.MultiplyVector(triViewed[0], triTransformed[0]);
        WorldToView.MultiplyVector(triViewed[1], triTransformed[1]);
        WorldToView.MultiplyVector(triViewed[2], triTransformed[2]);

        //* View to Projection (V2P) */
        static const auto outScreen = [this](Engine::Triangle t)->bool {
            return (t[0].x() < 0 || t[0].x() > _win_x || t[0].y() < 0 || t[0].y() > _win_y ||
                    t[1].x() < 0 || t[1].x() > _win_x || t[1].y() < 0 || t[1].y() > _win_y ||
                    t[2].x() < 0 || t[2].x() > _win_x || t[2].y() < 0 || t[2].y() > _win_y);
        };

        if (isVR) {
            Math::Vector vOffsetView = {0.5, 1, 0}; // +1.0f to move the center of the screen // *0.5f to scale the screen to 0-1
            VRLeftProjection.MultiplyVector(triProjected[0], triTransformed[0]);
            VRLeftProjection.MultiplyVector(triProjected[1], triTransformed[1]);
            VRLeftProjection.MultiplyVector(triProjected[2], triTransformed[2]);
            triProjected[0] = (triProjected[0] + vOffsetView) * 0.5f * _win_x;
            triProjected[1] = (triProjected[1] + vOffsetView) * 0.5f * _win_x;
            triProjected[2] = (triProjected[2] + vOffsetView) * 0.5f * _win_x;
            if (triProjected[0].x() < _win_x/2 && !outScreen(triProjected))
                newMesh->add(std::make_shared<Engine::Triangle>(triProjected));
            VRRightProjection.MultiplyVector(triProjected2[0], triTransformed[0]);
            VRRightProjection.MultiplyVector(triProjected2[1], triTransformed[1]);
            VRRightProjection.MultiplyVector(triProjected2[2], triTransformed[2]);
            Math::Vector vOffsetView2 = {1.5, 1, 0}; // +1.0f to move the center of the screen // *0.5f to scale the screen to 0-1
            triProjected2[0] = (triProjected2[0] + vOffsetView2) * 0.5f * _win_x;
            triProjected2[1] = (triProjected2[1] + vOffsetView2) * 0.5f * _win_x;
            triProjected2[2] = (triProjected2[2] + vOffsetView2) * 0.5f * _win_x;
            if (triProjected2[0].x() > _win_x/2 && !outScreen(triProjected))
                newMesh->add(std::make_shared<Engine::Triangle>(triProjected2));
        } else {
            Math::Vector vOffsetView = {1, 1, 0}; // +1.0f to move the center of the screen // *0.5f to scale the screen to 0-1
            ViewtoProjection.MultiplyVector(triProjected[0], triTransformed[0]);
            ViewtoProjection.MultiplyVector(triProjected[1], triTransformed[1]);
            ViewtoProjection.MultiplyVector(triProjected[2], triTransformed[2]);
            triProjected[0] = (triProjected[0] + vOffsetView) * 0.5f * _win_x;
            triProjected[1] = (triProjected[1] + vOffsetView) * 0.5f * _win_x;
            triProjected[2] = (triProjected[2] + vOffsetView) * 0.5f * _win_x;
            // if (!outScreen(triProjected)) {
                // std::cout << "triProjected[0].x() = " << triProjected[0].x() << std::endl;
                newMesh->add(std::make_shared<Engine::Triangle>(triProjected));
            // }
        }
    }
} // namespace Engine

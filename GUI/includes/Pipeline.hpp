/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Pipeline
*/

#ifndef PIPELINE_HPP_
    #define PIPELINE_HPP_
    #include "Camera.hpp"
    #include "Mesh.hpp"

namespace Engine {
    class Pipeline {
        public:
            Pipeline() = default;
            Pipeline(const Pipeline &cpy) = default;
            Pipeline(std::shared_ptr<Camera> cam, unsigned win_x, unsigned win_y) {
                VRLeftProjection.SetLeftEyeProjectionMatrix(120.0f, float(win_y/2) / float(win_x), 0.1f, 1000.0f);
                VRRightProjection.SetRightEyeProjectionMatrix(120.0f, float(win_y/2) / float(win_x), 0.1f, 1000.0f);
                ViewtoProjection.SetProjectionMatrix(120.0f, float(win_y) / float(win_x), 0.1f, 1000.0f);
                _win_x = win_x; _win_y = win_y;
                _cam = cam;
            }
            ~Pipeline() = default;

            void setCamera(std::shared_ptr<Camera> cam) { _cam = cam; }
            std::shared_ptr<Camera> &getCamera() { return _cam; }
            std::shared_ptr<Engine::Mesh> &getNewMesh() { return newMesh; }
            void setNewMesh(std::shared_ptr<Engine::Mesh> mesh) { newMesh = mesh; }
            void setWinSize(Math::Vector win_size) {
                _win_x = win_size.x(); _win_y = win_size.y();
                std::cout << "win_x: " << _win_x << " win_y: " << _win_y << std::endl;
                ViewtoProjection.SetProjectionMatrix(120.0f, float(_win_y) / float(_win_x), 0.1f, 1000.0f);
                VRLeftProjection.SetLeftEyeProjectionMatrix(120.0f, float(_win_y/2) / float(_win_x), 0.1f, 1000.0f);
                VRRightProjection.SetRightEyeProjectionMatrix(120.0f, float(_win_y/2) / float(_win_x), 0.1f, 1000.0f);
            }

            void geometry_rendering(Mesh &mesh, std::shared_ptr<Triangle> tri, bool isVR);

        protected:
        private:
            Math::Matrix ViewtoProjection;
            Math::Matrix VRLeftProjection;
            Math::Matrix VRRightProjection;
            std::shared_ptr<Camera> _cam = nullptr;
            unsigned _win_x, _win_y;
            //* Triangle to Raster (T2R) */
            std::shared_ptr<Engine::Mesh> newMesh = nullptr;
    };
} // namespace Engine

#endif /* !PIPELINE_HPP_ */

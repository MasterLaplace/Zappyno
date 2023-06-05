/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_
    #include "Panel.hpp"
    #include "Mesh.hpp"
    #include "Xml.hpp"

namespace GUI {
    class Scene {
        public:
            Scene() {}
            ~Scene() = default;
            Scene(Scene&) = default;
            Scene(Scene&&) = default;
            Scene(const Scene&) = default;
            Scene &operator=(const Scene&) = default;

            void addPanel(const Interface::Panel &panel) {
                _panels.push_back(panel);
            }

            void updateScene(const Math::Vector &mousePos, const bool &mousePressed = false) {
                for (auto &panel : _panels)
                    panel.updatePanel(mousePos, mousePressed);

            }
            void updateScene(const Math::Vector &mousePos, int key, const bool &mousePressed = false) {
                for (auto &panel : _panels)
                    panel.updatePanel(mousePos, key, mousePressed);
            }
            template<typename T>
            void drawScene(T &win) {
                for (auto &panel : _panels)
                    panel.drawPanel(win);
            }

        protected:
        private:
            std::vector<Interface::Panel> _panels;
    };


#endif /* !SCENE_HPP_ */

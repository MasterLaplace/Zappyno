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

    class SceneManager {
        public:
            enum SceneType {
                GAME,
                MENU,
                SETTING,
                CREATE,
                PAUSE,
                CREDIT,
                RESULT
            };
        public:
            SceneManager() {
                _xml = std::make_shared<Parser::Xml>();
                _xml->loadFile("GUI/assets/scene.xml");
            }
            ~SceneManager() = default;
            SceneManager(SceneManager&) = default;
            SceneManager(SceneManager&&) = default;
            SceneManager(const SceneManager&) = default;
            SceneManager &operator=(const SceneManager&) = default;

            static void switchPanel(std::vector<Interface::Panel> &panels, const std::string &panelName);
            static void switchScene(SceneType &actualScene, const SceneType &nextScene);
            static std::string SceneTypeToString(const SceneType &sceneType);
            static std::string findInTiles(std::vector<std::map<std::string, std::string>> tile, std::string compare, std::string key = "path");
            template<typename Win, typename Sprite>
            std::shared_ptr<Scene> create_scene(const SceneType &sceneType, std::shared_ptr<Win> window) {
                std::shared_ptr<Scene> scene = std::make_shared<Scene>();
                std::vector<std::map<std::string, std::string>> image = _xml->getTiles("GUI/assets/scene.xml", "Images");
                std::vector<std::map<std::string, std::string>> font = _xml->getTiles("GUI/assets/scene.xml", "Fonts");
                std::vector<std::map<std::string, std::string>> button = _xml->getTiles("GUI/assets/scene.xml", "Buttons");
                std::vector<std::map<std::string, std::string>> input = _xml->getTiles("GUI/assets/scene.xml", "Inputs");
                std::vector<std::map<std::string, std::string>> bar = _xml->getTiles("GUI/assets/scene.xml", "Bars");
                std::vector<std::map<std::string, std::string>> panel = _xml->getTiles("GUI/assets/scene.xml", "Panels");
                std::vector<std::map<std::string, std::string>> scenes = _xml->getTiles("GUI/assets/scene.xml", "Scenes");
                // loop on scene
                for (auto it : scenes) {
                    std::cout << "name scene: " << it["name"] << std::endl;
                    if (it["name"] == SceneManager::SceneTypeToString(sceneType)) {
                        auto ok = String::string_to_string_vector(it["panels"], ", \t");
                        for (auto it2 : ok) {
                            // loop on panel
                            for (auto it3 : panel) {
                                if (it3["name"] == it2) {
                                    std::cout << "name panel: " << it3["name"] << std::endl;
                                    std::vector<std::string> posComponents = String::string_to_string_vector(it3["pos"], ", \t");
                                    std::vector<std::string> scaleComponents = String::string_to_string_vector(it3["scale"], ", \t");
                                    Math::Vector pos(std::stof(posComponents[0]), std::stof(posComponents[1]));
                                    Math::Vector scale(std::stof(scaleComponents[0]), std::stof(scaleComponents[1]));
                                    Interface::Panel _panel = Interface::Panel(std::make_shared<Sprite>(window, findInTiles(image, it3["img"]), pos, scale));
                                    // loop on button
                                    auto buttons = String::string_to_string_vector(it3["buttons"], ", \t");
                                    std::cout << "buttons: " << it3["buttons"] << std::endl;
                                    for (auto it4 : buttons) {
                                        for (auto it5 : button) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name button: " << it5["name"] << std::endl;
                                                std::vector<std::string> posComponents = String::string_to_string_vector(it5["pos"], ", \t");
                                                std::vector<std::string> scaleComponents = String::string_to_string_vector(it5["scale"], ", \t");
                                                Math::Vector pos(std::stof(posComponents[0]), std::stof(posComponents[1]));
                                                Math::Vector scale(std::stof(scaleComponents[0]), std::stof(scaleComponents[1]));
                                                Interface::Button _button = Interface::Button(std::make_shared<Sprite>(window, findInTiles(image, it5["img"]), pos, scale));
                                                auto sprite = _button.getSprite();
                                                std::vector<std::string> offsetComponents = String::string_to_string_vector(findInTiles(image, it5["img"], "offset"), ", \t");
                                                sprite->setOffset(Math::Vector(std::stof(offsetComponents[0]), std::stof(offsetComponents[1])));
                                                sprite->setMaxOffsetX(std::stoi(findInTiles(image, it5["img"], "max")));
                                                _panel.addButton(_button);
                                            }
                                        }
                                    }
                                    scene->addPanel(_panel);
                                }
                            }
                        }
                        break;
                    }
                }
                return scene;
            }

        protected:
        private:
            std::shared_ptr<Parser::Xml> _xml;
    };
}

#endif /* !SCENE_HPP_ */

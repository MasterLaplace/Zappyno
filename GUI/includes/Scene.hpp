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
            std::vector<Interface::CALLBACK> getCallback() {
                std::vector<Interface::CALLBACK> callback;
                for (auto &panel : _panels) {
                    std::vector<Interface::CALLBACK> tmp = panel.getCallback();
                    callback.insert(callback.end(), tmp.begin(), tmp.end());
                }
                return callback;
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
                MENU,
                GAME,
                SETTING,
                CREATE,
                PAUSE,
                CREDIT,
                RESULT
            };
        public:
            SceneManager() {
                _xml.loadFile("GUI/assets/scene.xml");
            }
            ~SceneManager() = default;
            SceneManager(SceneManager&) = default;
            SceneManager(SceneManager&&) = default;
            SceneManager(const SceneManager&) = default;
            SceneManager &operator=(const SceneManager&) = default;

            static void switchPanel(std::vector<Interface::Panel> &panels, const std::string &panelName);
            static void switchScene(SceneType &actualScene, const SceneType &nextScene);
            static std::string SceneTypeToString(const SceneType &sceneType);
            static std::string CallbackToString(const Interface::CALLBACK &callback);
            static Interface::CALLBACK StringToCallback(const std::string &callback);
            static sf::Color StringToSfColor(const std::string &color);
            static std::string findInTiles(std::vector<std::map<std::string, std::string>> tile, std::string compare, std::string key = "path");
            template<typename Win, typename Sprite>
            std::shared_ptr<Scene> create_scene(const SceneType &sceneType, std::shared_ptr<Win> window) {
                std::shared_ptr<Scene> scene = std::make_shared<Scene>();
                std::vector<std::map<std::string, std::string>> image = _xml.getTiles("GUI/assets/scene.xml", "Images");
                std::vector<std::map<std::string, std::string>> font = _xml.getTiles("GUI/assets/scene.xml", "Fonts");
                std::vector<std::map<std::string, std::string>> button = _xml.getTiles("GUI/assets/scene.xml", "Buttons");
                std::vector<std::map<std::string, std::string>> input = _xml.getTiles("GUI/assets/scene.xml", "Inputs");
                std::vector<std::map<std::string, std::string>> bar = _xml.getTiles("GUI/assets/scene.xml", "Bars");
                std::vector<std::map<std::string, std::string>> panel = _xml.getTiles("GUI/assets/scene.xml", "Panels");
                std::vector<std::map<std::string, std::string>> scenes = _xml.getTiles("GUI/assets/scene.xml", "Scenes");
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
                                    Math::Vector pos(String::string_to_string_vector(it3["pos"], ", \t"));
                                    Math::Vector scale(String::string_to_string_vector(it3["scale"], ", \t"));
                                    Interface::Panel _panel = Interface::Panel(std::make_shared<Sprite>(window, findInTiles(image, it3["img"]), pos, scale));
                                    // loop on button
                                    auto buttons = String::string_to_string_vector(it3["buttons"], ", \t");
                                    std::cout << "buttons: " << it3["buttons"] << std::endl;
                                    for (auto it4 : buttons) {
                                        for (auto it5 : button) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name button: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                Math::Vector scale(String::string_to_string_vector(it5["scale"], ", \t"));
                                                Interface::Button _button = Interface::Button(std::make_shared<Sprite>(window, findInTiles(image, it5["img"]), pos, scale));
                                                auto sprite = _button.getSprite();
                                                std::vector<std::string> offsetComponents = String::string_to_string_vector(findInTiles(image, it5["img"], "offset"), ", \t");
                                                sprite->setOffset(Math::Vector(std::stof(offsetComponents[0]), std::stof(offsetComponents[1])));
                                                sprite->setMaxOffsetX(std::stoi(findInTiles(image, it5["img"], "max")));
                                                _button.setCallback(SceneManager::StringToCallback(it5["callback"]));
                                                _panel.addButton(_button);
                                            }
                                        }
                                    }
                                    // loop on input
                                    auto inputs = String::string_to_string_vector(it3["inputs"], ", \t");
                                    std::cout << "inputs: " << it3["input"] << std::endl;
                                    for (auto it4 : inputs) {
                                        for (auto it5 : input) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name input: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                auto fsize = std::stoi(it5["fsize"]);
                                                auto limit = std::stoi(it5["limit"]);
                                                Sf_text::Text_s tt("", {float(pos.x()), float(pos.y())}, Sf_text::createFont(findInTiles(font, it5["font"])), SceneManager::StringToSfColor(it5["color"]), fsize);
                                                Interface::Input _input = Interface::Input(pos, Math::Vector(fsize * limit, fsize), limit, tt);
                                                _panel.addInput(_input);
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

            template <typename Win, typename Sprite>
            void switchScene(std::shared_ptr<Win> window, std::shared_ptr<Scene> &scene) {
                std::vector<Interface::CALLBACK> list_callback = scene->getCallback();
                for (auto it : list_callback) {
                    switch (it) {
                        case Interface::CALLBACK::EXIT:
                            window->close();
                            return;
                        case Interface::CALLBACK::GOTO_MENU:
                            scene = create_scene<Win, Sprite>(SceneType::MENU, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREATE:
                            scene = create_scene<Win, Sprite>(SceneType::CREATE, window);
                            return;
                        case Interface::CALLBACK::GOTO_GAME:
                            scene = create_scene<Win, Sprite>(SceneType::GAME, window);
                            return;
                        case Interface::CALLBACK::GOTO_SETTING:
                            scene = create_scene<Win, Sprite>(SceneType::SETTING, window);
                            return;
                        case Interface::CALLBACK::GOTO_RESULT:
                            scene = create_scene<Win, Sprite>(SceneType::RESULT, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREDIT:
                            scene = create_scene<Win, Sprite>(SceneType::CREDIT, window);
                            return;
                        default:
                            break;
                    }
                }
            }

        protected:
        private:
            Parser::Xml _xml;
    };
}

#endif /* !SCENE_HPP_ */

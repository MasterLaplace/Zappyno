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
    #include <SFML/Audio.hpp>
    #include "Protocol.hpp"

namespace Scene_Manager {
    enum SceneType {
        MENU,
        GAME,
        SETTING,
        CREATE,
        PAUSE,
        CREDIT,
        RESULT
    };
}

namespace GUI {
    class Scene {
        public:
            Scene() = default;
            Scene(Scene_Manager::SceneType sceneType) : _scenetype(sceneType) {}
            ~Scene() = default;
            Scene(Scene&) = default;
            Scene(Scene&&) = default;
            Scene(const Scene&) = default;
            Scene &operator=(const Scene&) = default;


            Scene_Manager::SceneType &getSceneType() { return _scenetype; }

            std::shared_ptr<Interface::Chat> getChat();

            void addPanel(const Interface::Panel &panel) { _panels.push_back(panel); }

            void updateScene(const Math::Vector &mousePos, const bool &mousePressed = false);
            void updateScene(const Math::Vector &mousePos, int key, const bool &mousePressed = false);

            std::vector<Interface::CALLBACK> getCallback();

            template<typename T>
            void drawScene(T &win) {
                for (auto &panel : _panels)
                    panel.drawPanel(win);
            }

        protected:
        private:
            Scene_Manager::SceneType _scenetype;
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
                if (!music.openFromFile("GUI/assets/sounds/Outer_Wilds.ogg"))
                    throw std::invalid_argument("Core: Cannot load music file");
                music.play();
                music.setLoop(true);
            }
            ~SceneManager() = default;
            SceneManager(SceneManager&) = default;
            SceneManager(SceneManager&&) = default;
            SceneManager(const SceneManager&) = default;
            SceneManager &operator=(const SceneManager&) = default;

            static void switchPanel(std::vector<Interface::Panel> &panels, const std::string &panelName);
            static void switchScene(Scene_Manager::SceneType &actualScene, const Scene_Manager::SceneType &nextScene);
            static std::string SceneTypeToString(const Scene_Manager::SceneType &sceneType);
            static std::string CallbackToString(const Interface::CALLBACK &callback);
            static Interface::CALLBACK StringToCallback(const std::string &callback);
            static sf::Color StringToSfColor(const std::string &color);
            static std::string findInTiles(std::vector<std::map<std::string, std::string>> tile, std::string compare, std::string key = "path");
            template<typename Win, typename Sprite>
            std::shared_ptr<Scene> create_scene(const Scene_Manager::SceneType &sceneType, std::shared_ptr<Win> window) {
                std::shared_ptr<Scene> scene = std::make_shared<Scene>(sceneType);
                std::vector<std::map<std::string, std::string>> image = _xml.getTiles("GUI/assets/scene.xml", "Images");
                std::vector<std::map<std::string, std::string>> font = _xml.getTiles("GUI/assets/scene.xml", "Fonts");
                std::vector<std::map<std::string, std::string>> button = _xml.getTiles("GUI/assets/scene.xml", "Buttons");
                std::vector<std::map<std::string, std::string>> checkbox = _xml.getTiles("GUI/assets/scene.xml", "Checkboxs");
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
                                                sprite->setOffset(Math::Vector(String::string_to_string_vector(findInTiles(image, it5["img"], "offset"), ", \t")));
                                                sprite->setMaxOffsetX(std::stoi(findInTiles(image, it5["img"], "max")));
                                                _button.setCallback(SceneManager::StringToCallback(it5["callback"]));
                                                _panel.addButton(_button);
                                            }
                                        }
                                    }
                                    auto checkboxs = String::string_to_string_vector(it3["checkboxs"], ", \t");
                                    std::cout << "checkboxs: " << it3["checkboxs"] << std::endl;
                                    for (auto it4 : checkboxs) {
                                        for (auto it5 : checkbox) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name checkbox: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                Math::Vector scale(String::string_to_string_vector(it5["scale"], ", \t"));
                                                Interface::Checkbox _checkbox = Interface::Checkbox(std::make_shared<Sprite>(window, findInTiles(image, it5["img"]), pos, scale));
                                                auto sprite = _checkbox.getSprite();
                                                std::vector<std::string> offsetComponents = String::string_to_string_vector(findInTiles(image, it5["img"], "offset"), ", \t");
                                                sprite->setOffset(Math::Vector(std::stof(offsetComponents[0]), std::stof(offsetComponents[1])));
                                                sprite->setMaxOffsetX(std::stoi(findInTiles(image, it5["img"], "max")));
                                                _checkbox.setCallback(SceneManager::StringToCallback(it5["callback"]));
                                                _panel.addCheckbox(_checkbox);
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
            void switchScene(std::shared_ptr<Win> window, std::shared_ptr<Scene> &scene, std::shared_ptr<Manager::Protocol> &protocol) {
                std::vector<Interface::CALLBACK> list_callback = scene->getCallback();
                list_callback.push_back(protocol->getCallback());
                for (auto it : list_callback) {
                    switch (it) {
                        case Interface::CALLBACK::EXIT:
                            window->close();
                            return;
                        case Interface::CALLBACK::MUTE_SOUND:
                            if (music.getVolume() == 0)
                                music.setVolume(100);
                            else
                                music.setVolume(0);
                            return;
                        case Interface::CALLBACK::GOTO_MENU:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::MENU, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREATE:
                            protocol->setWinnerTeam("");
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::CREATE, window);
                            return;
                        case Interface::CALLBACK::GOTO_GAME:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::GAME, window);
                            return protocol->setChat(scene->getChat());
                        case Interface::CALLBACK::GOTO_SETTING:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::SETTING, window);
                            return;
                        case Interface::CALLBACK::GOTO_RESULT:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::RESULT, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREDIT:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::CREDIT, window);
                            return;
                        default:
                            break;
                    }
                }
            }

        protected:
        private:
            Parser::Xml _xml;
            sf::Music music;
    };
}

#endif /* !SCENE_HPP_ */

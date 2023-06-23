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

            std::shared_ptr<std::vector<Interface::Text>> getTextInventoryUser();
            std::shared_ptr<std::vector<Interface::Text>> getTextInventoryCase();

            std::vector<Interface::Panel> &getPanels() { return _panels; }

            void addPanel(const Interface::Panel &panel) { _panels.push_back(panel); }

            void updateScene(const Math::Vector &mousePos, const bool &mousePressed = false);
            void updateScene(const Math::Vector &mousePos, int key, const bool &mousePressed = false);

            std::vector<Interface::CALLBACK> getCallback();

            template<typename Win>
            void drawScene(Win &win, std::shared_ptr<Manager::Protocol> &protocol) {
                _background->drawSprite();
                if (_scenetype == Scene_Manager::SceneType::GAME)
                    protocol->draw();
                for (auto &panel : _panels)
                    panel.drawPanel(win);
            };

            template<typename Win>
            void setSprite(std::string path, Win &window) { _background = std::make_shared<Sf_sprite::SfSprite>(window, path, Math::Vector(1, 1)); }

        protected:
        private:
            Scene_Manager::SceneType _scenetype;
            std::vector<Interface::Panel> _panels;
            std::shared_ptr<ISprite> _background = nullptr;
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
                std::vector<std::map<std::string, std::string>> chat = _xml.getTiles("GUI/assets/scene.xml", "Chats");
                std::vector<std::map<std::string, std::string>> text = _xml.getTiles("GUI/assets/scene.xml", "Texts");
                // loop on scene
                for (auto it : scenes) {
                    std::cout << "name scene: " << it["name"] << std::endl;
                    if (it["name"] == SceneManager::SceneTypeToString(sceneType)) {
                        auto ok = String::string_to_string_vector(it["panels"], ", \t");
                        scene->setSprite(findInTiles(image, it["back"]), window);
                        for (auto it2 : ok) {
                            // loop on panel
                            for (auto it3 : panel) {
                                if (it3["name"] == it2) {
                                    std::cout << "name type: " << it3["type"] << std::endl;
                                    Math::Vector pos(String::string_to_string_vector(it3["pos"], ", \t"));
                                    Math::Vector scale(String::string_to_string_vector(it3["scale"], ", \t"));
                                    std::string path = findInTiles(image, it3["img"]);
                                    Interface::Panel _panel;
                                    if (path != "")
                                        _panel.setSprite(std::make_shared<Sprite>(window, path, pos, scale));
                                    else {
                                        _panel.setPos(pos);
                                        _panel.setScale(scale);
                                    }
                                    _panel.setType(it3["type"]);
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
                                    // loop on chat
                                    auto chats = String::string_to_string_vector(it3["chats"], ", \t");
                                    std::cout << "inputs: " << it3["chat"] << std::endl;
                                    for (auto it4 : chats) {
                                        for (auto it5 : chat) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name input: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                auto limit = std::stoi(it5["limit"]);
                                                Interface::Chat _chat(findInTiles(font, it5["font"]));
                                                _chat.setLimit(limit);
                                                _chat.setPos(pos);
                                                _panel.addChat(_chat);
                                            }
                                        }
                                    }
                                    // loop on text
                                    if (_panel.getType() == "inventory_user")
                                        _panel.setTextUser(std::make_shared<std::vector<Interface::Text>>());
                                    else if (_panel.getType() == "inventory_case")
                                        _panel.setTextCase(std::make_shared<std::vector<Interface::Text>>());
                                    auto texts = String::string_to_string_vector(it3["texts"], ", \t");
                                    std::cout << "inputs: " << it3["text"] << std::endl;
                                    for (auto it4 : texts) {
                                        for (auto it5 : text) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name input: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                Interface::Text _text(findInTiles(font, it5["font"]));
                                                _text.setPos(pos);
                                                if (_panel.getType() == "inventory_user")
                                                    _panel.addTextUser(_text);
                                                else if (_panel.getType() == "inventory_case")
                                                    _panel.addTextCase(_text);
                                            }
                                        }
                                    }
                                    scene->addPanel(_panel);
                                }
                            }
                        }
                    }
                }
                return scene;
            }

            template <typename Win, typename Sprite>
            void switchScene(std::shared_ptr<Win> window, std::shared_ptr<Scene> &scene, std::shared_ptr<Manager::Protocol> &protocol) {
                std::vector<Interface::CALLBACK> list_callback = scene->getCallback();
                // list_callback.push_back(protocol->getCallback());
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
                            // protocol->setWinnerTeam("");
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::CREATE, window);
                            return;
                        case Interface::CALLBACK::GOTO_GAME:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::GAME, window);
                            protocol->setChat(scene->getChat());
                            protocol->setTextInventoryUser(scene->getTextInventoryUser());
                            protocol->setTextInventoryCase(scene->getTextInventoryCase());
                            return;
                        case Interface::CALLBACK::GOTO_SETTING:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::SETTING, window);
                            return;
                        case Interface::CALLBACK::GOTO_RESULT:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::RESULT, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREDIT:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::CREDIT, window);
                            return;
                        case Interface::CALLBACK::OPEN_INVENTORY_USER:
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "inventory_user") {
                                    it.setUserData(protocol->getUserData(0));
                                    return it.setCallback(Interface::CALLBACK::OPEN_INVENTORY_USER);
                                }
                            }
                            throw std::invalid_argument("Scene: Cannot find inventory user panel");
                        case Interface::CALLBACK::OPEN_INVENTORY_CASE:
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "inventory_case") {
                                    it.setCaseData(protocol->getCaseData(0));
                                    return it.setCallback(Interface::CALLBACK::OPEN_INVENTORY_CASE);
                                }
                            }
                            throw std::invalid_argument("Scene: Cannot find inventory case panel");
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

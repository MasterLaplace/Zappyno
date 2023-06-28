/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Scene
*/

#ifndef SCENE_HPP_
    #define SCENE_HPP_
    #include "Panel.hpp"
    #include "Pipeline.hpp"
    #include "Xml.hpp"
    #include <SFML/Audio.hpp>
    #include "Obj.hpp"
    #include "SfPrimitive.hpp"
    #include "Popup.hpp"
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

            void setVR(const bool &isVR) { _isVR = isVR; }
            void setPause(bool isPause) { _isPause = isPause; }
            void setPauseSettings(bool isPauseSettings) { _isPauseSettings = isPauseSettings; }

            void setPipeline(Engine::Pipeline pipeline) { _pipeline = pipeline; }
            Engine::Pipeline &getPipeline() { return _pipeline; }

            Scene_Manager::SceneType &getSceneType() { return _scenetype; }

            std::shared_ptr<Interface::Chat> getChat();

            std::shared_ptr<std::vector<Interface::Text>> getTextInventoryUser();
            std::shared_ptr<std::vector<Interface::Text>> getTextInventoryCase();

            std::vector<Interface::Panel> &getPanels() { return _panels; }

            void addObject(const Engine::Mesh &obj) { _objects.push_back(obj); }
            void addPanel(const Interface::Panel &panel) { _panels.push_back(panel); }

            void updateScene(const Math::Vector &mousePos, const bool &mousePressed = false);
            void updateScene(const Math::Vector &mousePos, int key, const bool &mousePressed = false);

            std::vector<Interface::CALLBACK> getCallback();

            template<typename Win, typename Shape>
            void drawScene(std::shared_ptr<Win> &win, std::shared_ptr<Manager::Protocol> &protocol) {
                if (protocol->message != "") {
                    std::string path = "GUI/assets/popup.png";
                    auto win_size = win->getSize();
                    sf::Texture texture;
                    if (texture.loadFromFile(path)) {
                        auto size = texture.getSize();
                        auto sprite = std::make_shared<Sf_sprite::SfSprite>(win, path, Math::Vector(win_size.x, win_size.y / 5 + size.y / 2));
                        _popups.push_back(Interface::Popup(sprite, win_size.x, protocol->message));
                    }
                    protocol->message = "";
                }
                if (_background)
                    _background->drawSprite();
                if (_scenetype == Scene_Manager::SceneType::GAME)
                    protocol->draw();
                if (_scenetype == Scene_Manager::SceneType::MENU) {
                    auto &mesh = _pipeline.getNewMesh();
                    if (mesh) {
                        sort(mesh->getShapes().begin(), mesh->getShapes().end(), [](const std::shared_ptr<Engine::Triangle> &a, const std::shared_ptr<Engine::Triangle> &b) {
                            double az = (a->operator[](0).z() + a->operator[](1).z() + a->operator[](2).z()) / 3.0f;
                            double bz = (b->operator[](0).z() + b->operator[](1).z() + b->operator[](2).z()) / 3.0f;
                            return az > bz;
                        });

                        mesh->drawMesh<Win, Shape>(Sf_primitive::drawTriangle, *win);
                        mesh->getShapes().clear();
                    }
                }
                for (auto &panel : _panels)
                    panel.drawPanel(*win);
                for (auto it = _popups.begin(); it != _popups.end();) {
                    if (it->getState() == Interface::Popup::State::END) {
                        it = _popups.erase(it);
                    } else {
                        it->drawPopup<Win>(*win);
                        ++it;
                    }
                }
            };

            template<typename Win>
            void setSprite(std::string path, Win &window) { _background = std::make_shared<Sf_sprite::SfSprite>(window, path, Math::Vector(1, 1)); }

        protected:
        private:
            Scene_Manager::SceneType _scenetype;
            std::vector<Interface::Panel> _panels;
            std::vector<Interface::Popup> _popups;
            std::vector<Engine::Mesh> _objects;
            Engine::Pipeline _pipeline;
            std::shared_ptr<ISprite> _background = nullptr;
            Interface::CALLBACK _callback = Interface::CALLBACK::NONE;
            bool _isVR = false;
            bool _isPause = false;
            bool _isPauseSettings = false;
    };

    static std::vector<std::string /*music path*/> MUSIC = {
        {"GUI/assets/sounds/Main_Title.ogg"},
        {"GUI/assets/sounds/Outer_Wilds.ogg"},
        {"GUI/assets/sounds/Timber_Hearth.ogg"},
        {"GUI/assets/sounds/14.3_Billion_Years.ogg"},
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
                if (!music.openFromFile(MUSIC[0]))
                    throw std::invalid_argument("Core: Cannot load music file");
                music.play();
            }
            ~SceneManager() { music.stop(); }
            SceneManager(SceneManager&) = default;
            SceneManager(SceneManager&&) = default;
            SceneManager(const SceneManager&) = default;
            SceneManager &operator=(const SceneManager&) = default;

            sf::Music &getMusic() { return music; }

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
                std::vector<std::map<std::string, std::string>> objs = _xml.getTiles("GUI/assets/scene.xml", "Objs");
                std::vector<std::map<std::string, std::string>> button = _xml.getTiles("GUI/assets/scene.xml", "Buttons");
                std::vector<std::map<std::string, std::string>> checkbox = _xml.getTiles("GUI/assets/scene.xml", "Checkboxs");
                std::vector<std::map<std::string, std::string>> input = _xml.getTiles("GUI/assets/scene.xml", "Inputs");
                std::vector<std::map<std::string, std::string>> bar = _xml.getTiles("GUI/assets/scene.xml", "Bars");
                std::vector<std::map<std::string, std::string>> panel = _xml.getTiles("GUI/assets/scene.xml", "Panels");
                std::vector<std::map<std::string, std::string>> meshes = _xml.getTiles("GUI/assets/scene.xml", "Meshes");
                std::vector<std::map<std::string, std::string>> cameras = _xml.getTiles("GUI/assets/scene.xml", "Cameras");
                // std::vector<std::map<std::string, std::string>> text = _xml.getTiles("GUI/assets/scene.xml", "Texts");
                // std::vector<std::map<std::string, std::string>> checkbox = _xml.getTiles("GUI/assets/scene.xml", "CheckBoxes");
                // std::vector<std::map<std::string, std::string>> slider = _xml.getTiles("GUI/assets/scene.xml", "Sliders");
                // std::vector<std::map<std::string, std::string>> scrollBar = _xml.getTiles("GUI/assets/scene.xml", "ScrollBars");
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
                                    std::cout << "chats: " << it3["chat"] << std::endl;
                                    for (auto it4 : chats) {
                                        for (auto it5 : chat) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name chat: " << it5["name"] << std::endl;
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
                                    std::cout << "texts: " << it3["text"] << std::endl;
                                    for (auto it4 : texts) {
                                        for (auto it5 : text) {
                                            if (it5["name"] == it4) {
                                                std::cout << "name text: " << it5["name"] << std::endl;
                                                Math::Vector pos(String::string_to_string_vector(it5["pos"], ", \t"));
                                                Interface::Text _text(findInTiles(font, it5["font"]));
                                                _text.setPos(pos);
                                                _text.setColor(SceneManager::StringToSfColor(it5["color"]));
                                                if (it5.find("str") != it5.end())
                                                    _text.setText(it5["str"]);
                                                if (_panel.getType() == "inventory_user")
                                                    _panel.addTextUser(_text);
                                                else if (_panel.getType() == "inventory_case")
                                                    _panel.addTextCase(_text);
                                                else
                                                    _panel.addText(_text);
                                            }
                                        }
                                    }
                                    scene->addPanel(_panel);
                                }
                            }
                        }
                        std::vector<std::string> ok2;
                        if (it.find("meshes") != it.end())
                            ok2 = String::string_to_string_vector(it["meshes"], ", \t");
                        for (auto it2 : ok2) {
                            // loop on meshes
                            for (auto it3 : meshes) {
                                if (it3["name"] == it2) {
                                    std::cout << "name meshes: " << it3["name"] << std::endl;
                                    Engine::Mesh _mesh;
                                    if (it3.find("plan") != it3.end()) {
                                        Math::Vector size(String::string_to_string_vector(it3["plan"], ", \t"));

                                        for (int y = 0; y < size.y(); y++) {
                                            for (int x = 0; x < size.x(); x++) {
                                                Engine::Triangle tri(Math::Vector(x, y), Math::Vector((x + 1), y), Math::Vector((x + 1), (y + 1)));
                                                _mesh.add(std::make_shared<Engine::Triangle>(tri));
                                                Engine::Triangle tri2(Math::Vector(x, (y + 1)), Math::Vector((x + 1), (y + 1)), Math::Vector(x, y));
                                                _mesh.add(std::make_shared<Engine::Triangle>(tri2));
                                            }
                                        }
                                    } else if (it3.find("obj") != it3.end()) {
                                        _mesh = Parser::Obj::loadFile(findInTiles(objs, it3["obj"]));
                                    }
                                    // obj.setMesh(_mesh);
                                    _mesh.setPos(Math::Vector(String::string_to_string_vector(it3["pos"], ", \t")));
                                    _mesh.setRot(Math::Vector(String::string_to_string_vector(it3["rot"], ", \t")));
                                    _mesh.setScale(Math::Vector(String::string_to_string_vector(it3["scale"], ", \t")));
                                    // std::cout << "pos: " << obj.getPos() << std::endl;
                                    // std::cout << "rot: " << obj.getRot() << std::endl;
                                    // std::cout << "scale: " << obj.getScale() << std::endl;
                                    // std::cout << "mesh: " << obj.getMesh() << std::endl;
                                    scene->addObject(_mesh);
                                }
                            }
                        }
                        if (it.find("camera") != it.end() && it["camera"] != "") {
                            std::cout << "name camera: " << it["camera"] << std::endl;
                            Engine::Pipeline pipeline;
                            pipeline.setCamera(std::make_shared<Engine::Camera>());
                            pipeline.setNewMesh(std::make_shared<Engine::Mesh>());
                            pipeline.setWinSize(Math::Vector(String::string_to_string_vector(it["win"], ", \t")));
                            auto camera = pipeline.getCamera();
                            camera->setPos(Math::Vector(String::string_to_string_vector(findInTiles(cameras, it["camera"], "pos"), ", \t")));
                            camera->setDir(Math::Vector(String::string_to_string_vector(findInTiles(cameras, it["camera"], "dir"), ", \t")));
                            scene->setPipeline(pipeline);
                            scene->setVR(_isVR);
                        }
                    }
                }
                return scene;
            }

            template <typename Win, typename Sprite>
            void switchScene(std::shared_ptr<Win> window, std::shared_ptr<Scene> &scene, std::shared_ptr<Manager::Protocol> &protocol) {
                std::vector<Interface::CALLBACK> list_callback = scene->getCallback();
                auto callcackP = protocol->getCallback();
                list_callback.insert(list_callback.end(), callcackP.begin(), callcackP.end());
                try {
                    if (music.getStatus() == sf::SoundSource::Stopped) {
                        if (!music.openFromFile(MUSIC[RAND(0, 3)]))
                            throw std::invalid_argument("Core: Cannot load music file");
                        music.play();
                    }
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                if (scene->getSceneType() == Scene_Manager::SceneType::GAME) {
                    for (auto &it : scene->getPanels()) {
                        if (it.getType() == "score")
                            it.setText(protocol->getScore());
                    }
                }
                for (auto it : list_callback) {
                    switch (it) {
                        case Interface::CALLBACK::EXIT:
                            return window->close();
                        case Interface::CALLBACK::MUTE_SOUND:
                            if (music.getVolume() == 0)
                                music.setVolume(100);
                            else
                                music.setVolume(0);
                            break;
                        case Interface::CALLBACK::RESIZE:
                            if (_isFullscreen) {
                                _isFullscreen = false;
                                window->close();
                                window->create(sf::VideoMode(1920, 1080), "GUI", sf::Style::Default);
                            } else {
                                _isFullscreen = true;
                                window->close();
                                window->create(sf::VideoMode(1920, 1080), "GUI", sf::Style::Fullscreen);
                            }
                            break;
                        case Interface::CALLBACK::GOTO_MENU:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::MENU, window);
                            return;
                        case Interface::CALLBACK::GOTO_CREATE:
                            protocol->setWinnerTeam("");
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::CREATE, window);
                            return;
                        case Interface::CALLBACK::GOTO_GAME:
                            scene = create_scene<Win, Sprite>(Scene_Manager::SceneType::GAME, window);
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
                        case Interface::CALLBACK::OPEN_PAUSE:
                            if (scene->getSceneType() != Scene_Manager::SceneType::GAME)
                                break;
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "pause") {
                                    scene->setPause(true);
                                    return it.setCallback(Interface::CALLBACK::OPEN_PAUSE);
                                }
                            }
                            break;
                        case Interface::CALLBACK::GOTO_SETTING_PAUSE:
                            if (scene->getSceneType() != Scene_Manager::SceneType::GAME)
                                break;
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "pause_setting") {
                                    scene->setPauseSettings(true);
                                    return it.setCallback(Interface::CALLBACK::GOTO_SETTING_PAUSE);
                                }
                            }
                            break;
                        case Interface::CALLBACK::OPEN_INVENTORY_USER:
                            if (scene->getSceneType() != Scene_Manager::SceneType::GAME)
                                break;
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "inventory_user") {
                                    std::cout << "user id: " << protocol->getCallbackTileId() << std::endl;
                                    it.setUserData(protocol->getUserData(protocol->getCallbackTileId()));
                                    return it.setCallback(Interface::CALLBACK::OPEN_INVENTORY_USER);
                                }
                            }
                            break;
                        case Interface::CALLBACK::OPEN_INVENTORY_CASE:
                            if (scene->getSceneType() != Scene_Manager::SceneType::GAME)
                                break;
                            for (auto &it : scene->getPanels()) {
                                if (it.getType() == "inventory_case") {
                                    std::cout << "case id: " << protocol->getCallbackTileId() << std::endl;
                                    it.setCaseData(protocol->getCaseData(protocol->getCallbackUserId()));
                                    return it.setCallback(Interface::CALLBACK::OPEN_INVENTORY_CASE);
                                }
                            }
                            break;
                        case Interface::CALLBACK::VR:
                            _isVR = !_isVR;
                            scene->setVR(_isVR);
                            break;
                        default:
                            break;
                    }
                }
            }

        protected:
        private:
            Parser::Xml _xml;
            sf::Music music;
            bool _isVR = false;
            bool _isFullscreen = false;
            Math::Vector _winSize = {1920, 1080};
    };
} // namespace GUI

#endif /* !SCENE_HPP_ */

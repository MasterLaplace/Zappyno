/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Scene
*/

#include "../../includes/Scene.hpp"

namespace GUI {
    //* SCENE *//

    std::shared_ptr<Interface::Chat> Scene::getChat() {
        for (auto &panel : _panels) {
            auto chat = panel.getChat();
            if (chat != nullptr)
                return chat;
        }
        return nullptr;
    }

    void Scene::updateScene(const Math::Vector &mousePos, const bool &mousePressed) {
        for (auto &panel : _panels)
            panel.updatePanel(mousePos, mousePressed);
    }

    void Scene::updateScene(const Math::Vector &mousePos, int key, const bool &mousePressed) {
        for (auto &panel : _panels)
            panel.updatePanel(mousePos, key, mousePressed);
    }

    std::vector<Interface::CALLBACK> Scene::getCallback() {
        std::vector<Interface::CALLBACK> callback;
        for (auto &panel : _panels) {
            std::vector<Interface::CALLBACK> tmp = panel.getCallback();
            callback.insert(callback.end(), tmp.begin(), tmp.end());
        }
        return callback;
    }

    //* SCENE MANAGER *//

    void SceneManager::switchScene(Scene_Manager::SceneType &actualScene, const Scene_Manager::SceneType &nextScene) {
        actualScene = nextScene;
    }

    std::string SceneManager::SceneTypeToString(const Scene_Manager::SceneType &sceneType) {
        switch (sceneType) {
            case Scene_Manager::SceneType::GAME:
                return "game";
            case Scene_Manager::SceneType::MENU:
                return "menu";
            case Scene_Manager::SceneType::SETTING:
                return "setting";
            case Scene_Manager::SceneType::CREATE:
                return "create";
            case Scene_Manager::SceneType::PAUSE:
                return "pause";
            case Scene_Manager::SceneType::CREDIT:
                return "credit";
            case Scene_Manager::SceneType::RESULT:
                return "result";
            default:
                return "NONE";
        }
    }

    std::string SceneManager::CallbackToString(const Interface::CALLBACK &callback) {
        switch (callback) {
            case Interface::CALLBACK::GOTO_CREATE:
                return "goto_create";
            case Interface::CALLBACK::GOTO_GAME:
                return "goto_game";
            case Interface::CALLBACK::GOTO_SETTING:
                return "goto_setting";
            case Interface::CALLBACK::GOTO_CREDIT:
                return "goto_credit";
            case Interface::CALLBACK::GOTO_RESULT:
                return "goto_result";
            case Interface::CALLBACK::GOTO_MENU:
                return "goto_menu";
            case Interface::CALLBACK::RESIZE:
                return "resize";
            case Interface::CALLBACK::MUTE_SOUND:
                return "mute_sound";
            case Interface::CALLBACK::EXIT:
                return "exit";
        default:
            return "NONE";
        }
    }

    Interface::CALLBACK SceneManager::StringToCallback(const std::string &callback) {
        for (int i = 0; i < Interface::CALLBACK::EXIT; i++) {
            if (callback == CallbackToString(static_cast<Interface::CALLBACK>(i)))
                return static_cast<Interface::CALLBACK>(i);
        }
        return Interface::CALLBACK::NONE;
    }

    sf::Color SceneManager::StringToSfColor(const std::string &color) {
        if (color == "red")
            return sf::Color::Red;
        if (color == "green")
            return sf::Color::Green;
        if (color == "blue")
            return sf::Color::Blue;
        if (color == "yellow")
            return sf::Color::Yellow;
        if (color == "magenta")
            return sf::Color::Magenta;
        if (color == "cyan")
            return sf::Color::Cyan;
        if (color == "transparent")
            return sf::Color::Transparent;
        if (color == "white")
            return sf::Color::White;
        if (color == "black")
            return sf::Color::Black;
        return sf::Color::White;
    }

    std::string SceneManager::findInTiles(std::vector<std::map<std::string, std::string>> tile, std::string compare, std::string key) {
        for (auto &it : tile) {
            if (compare == it["name"]) {
                std::cout << "Final key: " << it[key] << std::endl;
                return it[key];
            }
        }
        return "";
    }
} // namespace GUI

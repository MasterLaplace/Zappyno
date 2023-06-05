/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Scene
*/

#include "../../includes/Scene.hpp"

namespace GUI {
    void SceneManager::switchScene(SceneType &actualScene, const SceneManager::SceneType &nextScene) {
        actualScene = nextScene;
    }
    std::string SceneManager::SceneTypeToString(const SceneManager::SceneType &sceneType) {
        switch (sceneType) {
            case SceneManager::GAME:
                return "game";
            case SceneManager::MENU:
                return "menu";
            case SceneManager::SETTING:
                return "setting";
            case SceneManager::CREATE:
                return "create";
            case SceneManager::PAUSE:
                return "pause";
            case SceneManager::CREDIT:
                return "credit";
            case SceneManager::RESULT:
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
    std::string SceneManager::findInTiles(std::vector<std::map<std::string, std::string>> tile, std::string compare, std::string key) {
        for (auto &it : tile) {
            if (compare == it["name"]) {
                std::cout << "Final key: " << it[key] << std::endl;
                return it[key];
            }
        }
        return "";
    }
}

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

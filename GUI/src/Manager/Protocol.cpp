/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Protocol
*/

#include "../../includes/Protocol.hpp"
#include <unordered_map>
#include <algorithm>

namespace Manager {
    void Protocol::parseCommand(std::string &str, std::shared_ptr<Client> client) {
        auto args = String::string_to_string_vector(str, "\n");

        std::unordered_map<std::string, std::vector<std::string>> map;
        for (auto av : args) {
            if (av == "WELCOME")
                return client->sendToServer("GRAPHIC\n");
            std::string command = av.substr(0, 3);
            if (map.find(command) == map.end())
                map[command] = std::vector<std::string>();
            map[command].push_back(av);
        }
        std::vector<std::pair<std::string, std::vector<std::string>>> reversedMap(map.begin(), map.end());

        std::reverse(reversedMap.begin(), reversedMap.end());

        for (auto &entry : reversedMap) {
            for (auto &value : entry.second) {
                if (commands.find(entry.first) != commands.end()) {
                    commands[entry.first](value);
                }
            }
        }
    }

    void Protocol::msz(std::string &str) {
        auto args = String::string_to_string_vector(str, " ");
        _mapSize = {std::stod(args[1]), std::stod(args[2])};
    }

}

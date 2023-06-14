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

    void Protocol::msz(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        _mapSize = {std::stod(args[1]), std::stod(args[2])};
    }

    void Protocol::bct(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        double x = std::stod(args[1]);
        double y = std::stod(args[2]);
        std::vector<unsigned> resources;

        for (int i = 3; i < 10; i++)
            resources.push_back(std::stoi(args[i]));
        if (_tiles.size() < _mapSize.x() * _mapSize.y())
            return _tiles.push_back(GUI::Tiles({x, y}, resources));
        for (auto &tile : _tiles) {
            if (tile.getPos().x() == x && tile.getPos().y() == y)
                return tile.setInventory(resources);
        }
    }

    void Protocol::tna(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");

        if (std::find(_teams.begin(), _teams.end(), args[1]) == _teams.end())
            _teams.push_back(args[1]);
    }

    void Protocol::pnw(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " #"); // Can generate bug if team name contains #
        unsigned id = std::stoi(args[1]);
        GUI::Trantorian player;

        player.setId(id);
        player.setPos({std::stod(args[2]), std::stod(args[3])});
        player.setDir(GUI::Trantorian::Direction(std::stoi(args[4])));
        player.setLevel(std::stoi(args[5]));
        player.setTeam(args[6]);
        for (auto &tile : _tiles) {
            if (tile.getPos().x() == player.getPos().x() && tile.getPos().y() == player.getPos().y())
                return tile.addTrantorian(player);
        }
    }
}

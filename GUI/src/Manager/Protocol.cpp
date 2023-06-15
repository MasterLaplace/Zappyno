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
        throw std::runtime_error("[bct] Tile not found in map (x: " + std::to_string(x) + ", y: " + std::to_string(y) + ")");
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
        if (_tiles.size() >= player.getPos().x() * player.getPos().y())
            return addTrantorian(player);
        throw std::runtime_error("[pnw] Player pos not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::ppo(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        Math::Vector pos = {std::stod(args[2]), std::stod(args[3])};

        for (auto &player : getTrantorians()) {
            if (player.getId() == id) {
                player.setPos({std::stod(args[2]), std::stod(args[3])});
                player.setDir(GUI::Trantorian::Direction(std::stoi(args[4])));
                return;
            }
        }
        throw std::runtime_error("[ppo] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::plv(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        for (auto &player : getTrantorians()) {
            if (player.getId() == id) {
                player.setLevel(std::stoi(args[2]));
                return;
            }
        }
        throw std::runtime_error("[plv] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pin(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        std::map<std::string, unsigned> inventory;
        inventory["food"] = std::stoi(args[4]);
        inventory["linemate"] = std::stoi(args[5]);
        inventory["deraumere"] = std::stoi(args[6]);
        inventory["sibur"] = std::stoi(args[7]);
        inventory["mendiane"] = std::stoi(args[8]);
        inventory["phiras"] = std::stoi(args[9]);
        inventory["thystame"] = std::stoi(args[10]);

        for (auto &player : getTrantorians()) {
            if (player.getId() == id)
                return player.setInventory(inventory);
        }
        throw std::runtime_error("[pin] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pex(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        for (auto &player : getTrantorians()) {
            if (player.getId() == id) {
                Math::Vector pos = player.getPos();
                GUI::Trantorian::Direction dir = player.getDir();
                Math::Vector newPos = pos;

                // get new pos by dir
                switch (dir) {
                    case GUI::Trantorian::Direction::NORTH:
                        newPos.operator[](1) -= 1;
                        break;
                    case GUI::Trantorian::Direction::EAST:
                        newPos.operator[](0) += 1;
                        break;
                    case GUI::Trantorian::Direction::SOUTH:
                        newPos.operator[](1) += 1;
                        break;
                    case GUI::Trantorian::Direction::WEST:
                        newPos.operator[](0) -= 1;
                        break;
                }

                // check limit map
                if (newPos.x() < 0)
                    newPos.operator[](0) = _mapSize.x() - 1;
                else if (newPos.y() < 0)
                    newPos.operator[](1) = _mapSize.y() - 1;
                else if (newPos.x() >= _mapSize.x())
                    newPos.operator[](0) = 0;
                else if (newPos.y() >= _mapSize.y())
                    newPos.operator[](1) = 0;

                // apply new pos
                for (auto &p : getTrantorians()) {
                    if (p.getPos() == pos && p.getId() != id)
                        p.setPos(newPos);
                }
                // destroy egg if on pos
                for (auto &egg : getEggs()) {
                    if (egg.getPos() == pos)
                        deleteEgg(egg.getId());
                }
                return;
            }
        }
        throw std::runtime_error("[pex] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pbc(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        std::string message = "";

        for (auto &arg : args) {
            if (arg == "smg")
                continue;
            if (arg == args[1])
                message += arg + ": ";
            else
                message += arg + " ";
        }
        if (message[message.size() - 1] == ' ')
            message[message.size() - 1] = '\0';
        _chat->addMessage(message);
    }

    GUI::Trantorian Protocol::getTrantorian(unsigned id) const {
        for (auto &trantorian : _trantorians) {
            if (trantorian.getId() == id)
                return trantorian;
        }
        throw std::runtime_error("[Protocol] Trantorian not found");
    }

    void Protocol::deleteTrantorian(unsigned id) {
        for (auto it = _trantorians.begin(); it != _trantorians.end(); it++) {
            if (it->getId() == id) {
                _trantorians.erase(it);
                break;
            }
        }
    }

    void Protocol::deleteEgg(unsigned id) {
        for (auto it = _eggs.begin(); it != _eggs.end(); it++) {
            if (it->getId() == id) {
                _eggs.erase(it);
                break;
            }
        }
    }
} // namespace GUI

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Protocol
*/

#include "../../includes/Protocol.hpp"
#include <unordered_map>
#include <algorithm>
#include <memory>

namespace Manager {
    void Protocol::parseCommand(std::string &str)
    {
        auto args = String::string_to_string_vector(str, "\n");

        std::unordered_map<std::string, std::vector<std::string>> map;
        for (auto av : args) {
            if (av == "WELCOME") {
                message = "Connection established";
                return _client->sendToServer("GRAPHIC\n");
            }
            std::string command = av.substr(0, 3);
            if (map.find(command) == map.end())
                map[command] = std::vector<std::string>();
            map[command].push_back(av);
        }
        std::vector<std::pair<std::string, std::vector<std::string>>> reversedMap(map.begin(), map.end());

        std::reverse(reversedMap.begin(), reversedMap.end());

        for (auto &entry : reversedMap) {
            for (auto &value : entry.second) {
                if (commands.find(entry.first) != commands.end())
                    commands[entry.first](value);
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
        static sf::Texture texture;

        for (int i = 3; i < 10; i++)
            resources.push_back(std::stoi(args[i]));
        if (_tiles.size() < _mapSize.x() * _mapSize.y()) {
            std::string path = "GUI/assets/tile.png";
            if (!texture.loadFromFile(path))
                return;
            auto size = texture.getSize();
            auto screen_size = _window->getSize();
            auto sprite = std::make_shared<Sf_sprite::SfSprite>(_window, path, Math::Vector(((screen_size.x / 2) - (((size.x) * _scale) * ((_mapSize.x() / 2) -1))) + ((size.x) * _scale) * x, ((screen_size.y / 2) - (((size.y / 4) * _scale) * ((_mapSize.y() / 2) -1))) + ((size.y / 4) * _scale) * y), Math::Vector(_scale, _scale));
            sprite->offset_y = size.y / 4;
            sprite->max_offset_x = 1;
            sprite->sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y / 4));
            return _tiles.push_back(GUI::Tiles(sprite, resources, _window));
        }
        for (unsigned i = 0; i < _tiles.size(); i++) {
            if (i == x + y * _mapSize.x())
                return _tiles[i].setInventory(resources, _scale);
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
        std::string path = "GUI/assets/trantorien_img.png";
        sf::Texture texture;
        if (!texture.loadFromFile(path))
            return;
        auto size = texture.getSize();
        auto tile = getTile({std::stod(args[2]), std::stod(args[3])});
        double scaleRatio = tile.getScaleRatio();
        auto randomPos = tile.getRandPos(path, _scale * scaleRatio);
        auto sprite = std::make_shared<Sf_sprite::SfSprite>(_window, path, randomPos, Math::Vector(_scale * scaleRatio, _scale * scaleRatio));
        auto trantorian = std::make_shared<GUI::Trantorian>();
        trantorian->setOriginalPos(randomPos - tile.getPos());
        trantorian->setId(id);
        trantorian->setDir(GUI::Trantorian::Direction(std::stoi(args[4])));
        trantorian->setLevel(std::stoi(args[5]));
        trantorian->setTeam(args[6]);

        sprite->offset_y = size.y / 8;
        sprite->offset_x = size.x / 4;
        sprite->max_offset_x = 4;

        sprite->sprite.setTextureRect(sf::IntRect(0, 0, sprite->offset_x, sprite->offset_y));
        trantorian->setSprite(sprite);
        if (std::stod(args[3]) * _mapSize.x() + std::stod(args[2]) <= _tiles.size())
            return _tiles[_mapSize.x() * std::stod(args[3]) + std::stod(args[2])].addTrantorian(trantorian);
        throw std::runtime_error("[pnw] Player pos not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::ppo(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        Math::Vector npos = {std::stod(args[2]), std::stod(args[3])};

        std::cout << "[ppo@Protocol] Trantorian moved: " << args[2] << " " << args[3] << std::endl;
        auto trantorian = getTile(id);
        if (trantorian) {
            trantorian->setNextPos(getTile(npos).getPos() + trantorian->getOriginalPos() * _scale * _tiles[0].getScaleRatio());
            trantorian->setNextPosId(npos.x() + npos.y() * _mapSize.x());
            return trantorian->setDir(GUI::Trantorian::Direction(std::stoi(args[4])));
        }
        throw std::runtime_error("[ppo] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::plv(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        auto trantorian = getTile(id);
        if (trantorian && int(trantorian->getLevel()) < std::stoi(args[2])) {
            message = "Player " + std::to_string(id) + " level up to " + args[2];
            return trantorian->setLevel(std::stoi(args[2]));
        }
    }

    void Protocol::pin(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        auto trantorian = getTile(id);

        if (trantorian)
            return trantorian->setFood("food", std::stoi(args[4]));
        throw std::runtime_error("[pin] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pex(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        auto trantorian = getTile(id);
        if (trantorian) {
            Math::Vector pos = trantorian->getPos();
            GUI::Trantorian::Direction dir = trantorian->getDir();
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
            auto tile = getTile(pos);
            for (auto &p : tile.getTrantorians()) {
                if (p->getPos() == pos && p->getId() != id)
                    p->setPos(newPos);
            }
            // destroy egg if on pos
            tile.removeEggs();
            return trantorian->setState(GUI::Trantorian::State::EXPULSING);
        }
        throw std::runtime_error("[pex] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pbc(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        std::string msg = args[1] + ": ";

        auto trantorian = getTile(id);
        if (trantorian)
            trantorian->setState(GUI::Trantorian::State::BROADCASTING);
        // start from 2 to skip id and "pbc"
        for (unsigned i = 2; i < args.size(); i++)
            msg += args[i] + " ";
        if (msg[msg.size() - 1] == ' ')
            msg[msg.size() - 1] = '\0';
        std::cout << "[pbc@Protocol] msg: " << msg << std::endl;
        message = msg;
    }

    void Protocol::pic(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        Math::Vector pos = {std::stod(args[2]), std::stod(args[3])};

        auto tile = getTile(pos);
        for (auto &trantorian : tile.getTrantorians()) {
            if (trantorian->getId() == id)
                trantorian->setState(GUI::Trantorian::State::INCANTING);
        }
    }

    void Protocol::pie(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        Math::Vector pos = {std::stod(args[1]), std::stod(args[2])};
        bool success = std::stoi(args[3]);

        for (auto &trantorian : getTile(pos).getTrantorians()) {
            if (success)
                trantorian->setState(GUI::Trantorian::State::IDLE); // Temporary
            else
                trantorian->setState(GUI::Trantorian::State::DYING); // Temporary
        }
    }

    void Protocol::pfk(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        auto trantorian = getTile(id);
        if (trantorian)
            return trantorian->setState(GUI::Trantorian::State::FORKING);
        throw std::runtime_error("[pfk] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pdr(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        std::cout << "[pdr] pdr" << std::endl;
        auto trantorian = getTile(id);
        for (auto &tile : _tiles) {
            for (auto &trantorian : tile.getTrantorians()) {
                if (trantorian->getId() == id) {
                    trantorian->removeFood(std::stoi(args[2]), 1);
                    tile.addFood(trantorian->intToFoodString(std::stoi(args[2])), _scale);
                    return trantorian->setState(GUI::Trantorian::State::DROPPING);
                }
            }
        }
        throw std::runtime_error("[pdr] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pgt(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);
        unsigned food = std::stoi(args[2]);

        for (auto &tile : _tiles) {
            for (auto &trantorian : tile.getTrantorians()) {
                if (trantorian->getId() == id) {
                    trantorian->addFood(food, 1);
                    tile.removeFood(trantorian->intToFoodString(food));
                    return trantorian->setState(GUI::Trantorian::State::TAKING);
                }
            }
        }
        throw std::runtime_error("[pgt] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::pdi(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        for (auto &tile : _tiles) {
            for (auto &trantorian : tile.getTrantorians()) {
                if (trantorian->getId() == id) {
                    message = "Player " + std::to_string(id) + " died";
                    return tile.removeTrantorian(trantorian);
                }
            }
        }
        throw std::runtime_error("[pdi] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::enw(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[2]);

        auto tile = getTile({std::stod(args[3]), std::stod(args[4])});
        auto trantorian = tile.getTrantorian(id);
        if (trantorian) {
            double scaleRatio = tile.getScaleRatio();
            auto randomPos = tile.getRandPos("GUI/assets/rock_assets/egg.png", _scale * scaleRatio);
            auto sprite = std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/egg.png", randomPos, Math::Vector(_scale * scaleRatio, _scale * scaleRatio));
            auto egg = std::make_shared<GUI::Egg>(sprite);
            egg->setOriginalPos(randomPos - tile.getPos());
            egg->setId(std::stoi(args[1]));
            egg->setTeam(trantorian->getTeam());
            return tile.addEgg(egg);
        }
        throw std::runtime_error("[enw] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::ebo(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        if (getEgg(id))
            return;
        throw std::runtime_error("[ebo] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::edi(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        unsigned id = std::stoi(args[1]);

        auto egg = getEgg(id);
        if (egg)
            return deleteEgg(id);
        throw std::runtime_error("[edi] Player not found in map (id: " + std::to_string(id) + ")");
    }

    void Protocol::sgt(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        _timeUnit = std::stoi(args[1]);
    }

    void Protocol::sst(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        _timeUnit = std::stoi(args[1]);
    }

    void Protocol::seg(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");

        if (std::find(_teams.begin(), _teams.end(), args[1]) == _teams.end())
            throw std::runtime_error("[seg] Team not found in vector (name: " + args[1] + ")");
        _winnerTeam = args[1];
        _gotoResult = Interface::CALLBACK::GOTO_RESULT;
    }

    void Protocol::smg(std::string &str)
    {
        auto args = String::string_to_string_vector(str, " ");
        std::string msg = "Global msg: ";

        // start at 1 to skip "smg"
        for (unsigned i = 1; i < args.size(); i++)
            msg += args[i] + " ";
        if (msg[msg.size() - 1] == ' ')
            msg[msg.size() - 1] = '\0';
        std::cout << msg << std::endl;
        message = msg;
    }

    void Protocol::suc(std::string &str)
    {
        throw std::runtime_error("[" + str + "] Unknown command");
    }

    void Protocol::sbp(std::string &str)
    {
        throw std::runtime_error("[" + str + "] Invalid argument");
    }

    GUI::Tiles &Protocol::getTile(Math::Vector pos) {
        if (pos.y() * _mapSize.x() + pos.x() >= _tiles.size())
            throw std::runtime_error("[getTile] Pos is out of map (x: " + std::to_string(pos.x()) + ", y: " + std::to_string(pos.y()) + ")");
        return _tiles[pos.y() * _mapSize.x() + pos.x()];
    }
    std::shared_ptr<GUI::Trantorian> Protocol::getTile(unsigned id) {
        for (auto &tile : _tiles) {
            for (auto &player : tile.getTrantorians()) {
                if (player->getId() == id)
                    return player;
            }
        }
        return nullptr;
    }
    std::shared_ptr<GUI::Egg> Protocol::getEgg(unsigned id) {
        for (auto &tile : _tiles) {
            for (auto &egg : tile.getEggs()) {
                if (egg->getId() == id)
                    return egg;
            }
        }
        return nullptr;
    }

    void Protocol::deleteEgg(unsigned id) {
        for (auto &tile : _tiles) {
            for (auto it = tile.getEggs().begin(); it != tile.getEggs().end(); it++) {
                if ((*it)->getId() == id) {
                    tile.getEggs().erase(it);
                    return;
                }
            }
        }
    }

    void Protocol::move_map(Math::Vector pos) {
        for (auto &tile : _tiles) {
            tile.setPos(tile.getPos() + pos);
            for (auto &food : tile.getFoods())
                food.setPos(food.getPos() + pos);
            for (auto &trantorian : tile.getTrantorians()) {
                trantorian->setPos(trantorian->getPos() + pos);
                trantorian->setNextPos(trantorian->getNextPos() + pos);
            }
            for (auto &egg : tile.getEggs())
                egg->setPos(egg->getPos() + pos);
        }
    }

    void Protocol::updatePosition() {
        unsigned x = 0;
        unsigned y = 0;
        Math::Vector midle_pos = _tiles[_tiles.size() / 2 + _mapSize.x() / 2].getPos();

        for (auto &tile : _tiles) {
            if (x == _mapSize.x()) {
                x = 0;
                y++;
            }
            if (_scale <= 0) {
                x++;
                continue;
            }
            tile.setScale({_scale, _scale});
            Math::Vector sizeOfTile = tile.getSize();

            /*
            * Calculate updated tile position by scale :
                MiddlePos - ((SizeMapPxl * scale) / 2) + (SizeTile * scale) * x
                MiddlePos - MiddleSizeMapPxl + PosTileInMapPxl
            */
            double updatedX = ((midle_pos.x()) - (sizeOfTile.x() * _mapSize.x() * _scale / 2)) + (sizeOfTile.x() * _scale) * x;
            double updatedY = ((midle_pos.y()) - (sizeOfTile.y() * _mapSize.y() * _scale / 2)) + (sizeOfTile.y() * _scale) * y;

            tile.setPos(Math::Vector(updatedX, updatedY));
            for (auto &trantorian : tile.getTrantorians())
            {
                trantorian->setScale({_scale * tile.getScaleRatio(), _scale * tile.getScaleRatio()});
                auto origin = trantorian->getOriginalPos();
                /*                          posTile  +   offest    *  scale */
                double TrantorianUpdatedX = updatedX + (origin.x() * _scale);
                double TrantorianUpdatedY = updatedY + (origin.y() * _scale);
                trantorian->setPos({TrantorianUpdatedX, TrantorianUpdatedY});
                if (trantorian->getNextPosId() == -1)
                    continue;
                sizeOfTile = _tiles[trantorian->getNextPosId()].getSize();

                TrantorianUpdatedX = ((midle_pos.x()) - (sizeOfTile.x() * _mapSize.x() * _scale / 2)) + (sizeOfTile.x() * _scale) * x + (origin.x() * _scale);
                TrantorianUpdatedY = ((midle_pos.y()) - (sizeOfTile.y() * _mapSize.y() * _scale / 2)) + (sizeOfTile.y() * _scale) * y + (origin.y() * _scale);

                trantorian->setNextPos({TrantorianUpdatedX, TrantorianUpdatedY});
            }
            for (auto &food : tile.getFoods())
            {
                food.setScale({_scale * tile.getScaleRatio(), _scale * tile.getScaleRatio()});
                auto origin = food.getOriginalPos();
                /*                    posTile  +   offest    *  scale */
                double FoodUpdatedX = updatedX + (origin.x() * _scale);
                double FoodUpdatedY = updatedY + (origin.y() * _scale);
                food.setPos({FoodUpdatedX, FoodUpdatedY});
            }
            for (auto &egg : tile.getEggs())
            {
                egg->setScale({_scale * tile.getScaleRatio(), _scale * tile.getScaleRatio()});
                auto origin = egg->getOriginalPos();
                /*                   posTile  +   offest    *  scale */
                double EggUpdatedX = updatedX + (origin.x() * _scale);
                double EggUpdatedY = updatedY + (origin.y() * _scale);
                egg->setPos({EggUpdatedX, EggUpdatedY});
            }
            x++;
        }
    }

    std::vector<std::string> Protocol::getScore() {
        std::map<std::string, int> scores;
        std::map<std::string, int> levels;
        std::vector<std::string> result;
        int division = 0;

        for (auto &tile : _tiles) {
            for (auto &trantorian : tile.getTrantorians()) {
                if (scores.find(trantorian->getTeam()) == scores.end())
                    scores[trantorian->getTeam()] = 1;
                else
                    scores[trantorian->getTeam()]++;
                if (levels.find(trantorian->getTeam()) == levels.end())
                    levels[trantorian->getTeam()] = trantorian->getLevel();
                else
                    levels[trantorian->getTeam()] += trantorian->getLevel();
                division++;
            }
        }
        for (auto &level : levels)
            level.second = level.second / division;

        std::vector<std::pair<std::string, int>> sortedLevels(levels.begin(), levels.end());

        std::sort(sortedLevels.begin(), sortedLevels.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        for (const auto &level : sortedLevels) {
            result.push_back(level.first + " > players: " + std::to_string(scores[level.first]));
        }
        return result;
    }

    std::vector<unsigned> Protocol::getUserData(unsigned id) {
        std::vector<unsigned> data(7);
        if (_tiles.size() < id || _tiles.empty())
            return std::vector<unsigned>(7, 0);
        for (auto food : _tiles[id].getFoods())
            data[static_cast<size_t>(food.getType())]++;
        return data;
    }

    std::vector<unsigned> Protocol::getCaseData(unsigned id) {
        std::vector<unsigned> data(7);
        if (_tiles.size() < id || _tiles.empty())
            return std::vector<unsigned>(7, 0);
        for (auto food : _tiles[id].getFoods())
            data[static_cast<size_t>(food.getType())]++;
        return data;
    }

    int Protocol::getCallbackTileId() {
        auto user = _tileId;
        return user;
    }
    int Protocol::getCallbackUserId() {
        auto user = _userId;
        return user;
    }

    void Protocol::draw() {
        for (auto &tile : _tiles)
            tile.drawTile();
        for (auto &tile : _tiles) {
            tile.drawFoods();
            tile.drawTrantorians();
            tile.drawEggs();
        }
    }
} // namespace GUI

/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Tiles
*/

#include "../../includes/Tiles.hpp"

namespace GUI {
    Tiles::Tiles(std::shared_ptr<ISprite> sprite, std::vector<unsigned> &inventory, std::shared_ptr<sf::RenderWindow> &window) {
        _window = window;
        _sprite = sprite;
        setInventory(inventory);
    }

    Math::Vector Tiles::getRandPos(std::string path, double scale) {
        auto pos = _sprite->getPos();
        auto size = _sprite->getSize();
        sf::Texture texture;
        texture.loadFromFile(path);
        auto p_size = texture.getSize();
        return Math::Vector(RAND(pos.x(), pos.x() + size.x() - (p_size.x * scale)), RAND(pos.y(), pos.y() + size.y() - (p_size.y * scale)));
    }

    void Tiles::setInventory(std::vector<unsigned> &inventory) {
        auto pos = _sprite->getPos();
        auto size = _sprite->getSize();
        std::map<std::string, unsigned> foods = {
            {"food", 0},
            {"linemate", 0},
            {"deraumere", 0},
            {"sibur", 0},
            {"mendiane", 0},
            {"phiras", 0},
            {"thystame", 0}
        };

        for (auto &food : _food) {
            if (food.getName() == "food")
                foods["food"]++;
            else if (food.getName() == "linemate")
                foods["linemate"]++;
            else if (food.getName() == "deraumere")
                foods["deraumere"]++;
            else if (food.getName() == "sibur")
                foods["sibur"]++;
            else if (food.getName() == "mendiane")
                foods["mendiane"]++;
            else if (food.getName() == "phiras")
                foods["phiras"]++;
            else if (food.getName() == "thystame")
                foods["thystame"]++;
        }
        for (unsigned i = foods["food"]; i < inventory[0]; i++) {
            auto randomPos = getRandPos(FOODS["food"], scaleRatio);
            Food food("food", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["food"], getRandPos(FOODS["food"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["linemate"]; i < inventory[1]; i++) {
            auto randomPos = getRandPos(FOODS["linemate"], scaleRatio);
            Food food("linemate", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["linemate"], getRandPos(FOODS["linemate"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["deraumere"]; i < inventory[2]; i++) {
            auto randomPos = getRandPos(FOODS["deraumere"], scaleRatio);
            Food food("deraumere", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["deraumere"], getRandPos(FOODS["deraumere"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["sibur"]; i < inventory[3]; i++) {
            auto randomPos = getRandPos(FOODS["sibur"], scaleRatio);
            Food food("sibur", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["sibur"], getRandPos(FOODS["sibur"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["mendiane"]; i < inventory[4]; i++) {
            auto randomPos = getRandPos(FOODS["mendiane"], scaleRatio);
            Food food("mendiane", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["mendiane"], getRandPos(FOODS["mendiane"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["phiras"]; i < inventory[5]; i++) {
            auto randomPos = getRandPos(FOODS["phiras"], scaleRatio);
            Food food("phiras", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["phiras"], getRandPos(FOODS["phiras"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
        for (unsigned i = foods["thystame"]; i < inventory[6]; i++) {
            auto randomPos = getRandPos(FOODS["thystame"], scaleRatio);
            Food food("thystame", std::make_shared<Sf_sprite::SfSprite>(_window, FOODS["thystame"], getRandPos(FOODS["thystame"], scaleRatio), Math::Vector(scaleRatio, scaleRatio)));
            food.setOriginalPos(randomPos - _sprite->getPos());
            _food.push_back(food);
        }
    }

    std::shared_ptr<GUI::Trantorian> Tiles::getTrantorian(unsigned id) {
        for (auto &trantorian : _trantorians) {
            if (trantorian->getId() == id)
                return trantorian;
        }
        return nullptr;
    }

    std::shared_ptr<GUI::Egg> Tiles::getEgg(unsigned id) {
        for (auto &egg : _eggs) {
            if (egg->getId() == id)
                return egg;
        }
        return nullptr;
    }

    void Tiles::addFood(const std::string &food) {
        auto randomPos = getRandPos(FOODS[food], scaleRatio);
        Food newFood(food, std::make_shared<Sf_sprite::SfSprite>(_window, FOODS[food], randomPos, Math::Vector(scaleRatio, scaleRatio)));
        newFood.setOriginalPos(randomPos - _sprite->getPos());
        _food.push_back(newFood);
    }

    void Tiles::removeFood(std::string food) {
        for (auto it = _food.begin(); it != _food.end(); it++) {
            if (it->getName() == food) {
                _food.erase(it);
                break;
            }
        }
    }

    void Tiles::removeTrantorian(std::shared_ptr<GUI::Trantorian> trantorian) {
        for (auto it = _trantorians.begin(); it != _trantorians.end(); it++) {
            if (*it == trantorian) {
                _trantorians.erase(it);
                break;
            }
        }
    }

    void Tiles::removeEgg(std::shared_ptr<GUI::Egg> egg) {
        for (auto it = _eggs.begin(); it != _eggs.end(); it++) {
            if (*it == egg) {
                _eggs.erase(it);
                break;
            }
        }
    }

    void Tiles::drawFoods() {
        for (auto &food : _food)
            food.drawFood();
    }
    void Tiles::drawTrantorians() {
        for (auto &trantorian : _trantorians)
            trantorian->drawTrantorian();
    }
    void Tiles::drawEggs() {
        for (auto &egg : _eggs)
            egg->drawEgg();
    }

    std::ostream &operator<<(std::ostream &os, Tiles &tile) {
        os << "Tile pos: " << tile.getPos() << std::endl;
        os << "Tile size: " << tile.getSize() << std::endl;
        os << "Tile inventory: " << std::endl;
        for (auto &it : tile.getInventory())
            os << "\t" << it.first << ": " << it.second << std::endl;
        os << "Tile foods: " << tile.getFoods().size() << std::endl;
        os << "Tile trantorians: " << tile.getTrantorians().size() << std::endl;
        os << "Tile eggs: " << tile.getEggs().size() << std::endl;
        return os;
    }
} // namespace GUI

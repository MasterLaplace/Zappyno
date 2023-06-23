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

    Math::Vector Tiles::getRandPos() {
        auto pos = _sprite->getPos();
        auto size = _sprite->getSize();
        return Math::Vector(RAND(pos.x(), pos.x() + size.x()), RAND(pos.y(), pos.y() + size.y()));
    }

    void Tiles::setInventory(std::vector<unsigned> &inventory) {
        auto pos = _sprite->getPos();
        auto size = _sprite->getSize();
        for (unsigned i = 0; i < inventory[0]; i++) {
            _food.push_back(Food("food", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_0.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[1]; i++) {
            _food.push_back(Food("linemate", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_1.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[2]; i++) {
            _food.push_back(Food("deraumere", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_2.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[3]; i++) {
            _food.push_back(Food("sibur", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_3.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[4]; i++) {
            _food.push_back(Food("mendiane", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_4.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[5]; i++) {
            _food.push_back(Food("phiras", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_5.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
        }
        for (unsigned i = 0; i < inventory[6]; i++) {
            _food.push_back(Food("thystame", std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/rock_assets/rock_6.png", getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
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
        _food.push_back(Food(food, std::make_shared<Sf_sprite::SfSprite>(_window, FOODS[food], getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
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

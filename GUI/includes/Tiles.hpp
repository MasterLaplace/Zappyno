/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Tiles
*/

#ifndef TILES_HPP_
    #define TILES_HPP_
    #define RAND(min, max) (rand() % static_cast<int>(max - min + 1) + min)
    #include "Vector.hpp"
    #include "Food.hpp"
    #include "SfSprite.hpp"
    #include <map>

namespace GUI {
    static std::map<const std::string /* food name */, const std::string /* texture path */> FOODS = {
        {"food", "GUI/assets/rock_assets/rock_0.png"},
        {"linemate", "GUI/assets/rock_assets/rock_1.png"},
        {"deraumere", "GUI/assets/rock_assets/rock_2.png"},
        {"sibur", "GUI/assets/rock_assets/rock_3.png"},
        {"mendiane", "GUI/assets/rock_assets/rock_4.png"},
        {"phiras", "GUI/assets/rock_assets/rock_5.png"},
        {"thystame", "GUI/assets/rock_assets/rock_6.png"}
    };
    class Tiles {
        public:
            Tiles(std::shared_ptr<ISprite> sprite, std::vector<unsigned> &inventory, std::shared_ptr<sf::RenderWindow> &window) {
                _window = window;
                _sprite = sprite;
                setInventory(inventory);
            }
            ~Tiles() = default;

            Math::Vector getRandPos() {
                auto pos = _sprite->getPos();
                auto size = _sprite->getSize();
                return Math::Vector(RAND(pos.x(), pos.x() + size.x()), RAND(pos.y(), pos.y() + size.y()));
            }

            void setPos(Math::Vector pos) { _sprite->setPos(pos); }
            void setScale(Math::Vector scale) { _sprite->setScale(scale); }
            void setInventory(std::vector<unsigned> &inventory) {
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

            Math::Vector getPos() const { return _sprite->getPos(); }
            Math::Vector getSize() const { return _sprite->getSize(); }
            std::map<std::string, unsigned> getInventory() const { return _inventory; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            std::vector<Food> getFoods() const { return _food; }
            double getScaleRatio() const { return scaleRatio; }

            void addFood(const std::string &food) {
                _food.push_back(Food(food, std::make_shared<Sf_sprite::SfSprite>(_window, FOODS[food], getRandPos(), Math::Vector(scaleRatio, scaleRatio))));
            }
            void removeFood(std::string food) {
                for (auto it = _food.begin(); it != _food.end(); it++) {
                    if (it->getName() == food) {
                        _food.erase(it);
                        break;
                    }
                }
            }

            void drawTile() { _sprite->drawSprite(); }
            void drawFoods() {
                for (auto &food : _food)
                    food.drawFoods();
            }

        protected:
        private:
            std::shared_ptr<sf::RenderWindow> _window = nullptr;
            std::shared_ptr<ISprite> _sprite = nullptr;
            std::vector<Food> _food;
            double scaleRatio = 0.35;
            std::map<std::string /* food name */, unsigned /* food quantity */> _inventory;
    };
} // namespace GUI

#endif /* !TILES_HPP_ */

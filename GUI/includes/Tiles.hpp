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
    #include "Trantorian.hpp"
    #include "Egg.hpp"
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
            Tiles(std::shared_ptr<ISprite> sprite, std::vector<unsigned> &inventory, std::shared_ptr<sf::RenderWindow> &window);
            ~Tiles() = default;

            Math::Vector getRandPos(std::string path, double scale = 1);

            void setPos(Math::Vector pos) { _sprite->setPos(pos); }
            void setScale(Math::Vector scale) { _sprite->setScale(scale); }
            void setInventory(std::vector<unsigned> &inventory);
            Math::Vector getPos() const { return _sprite->getPos(); }
            Math::Vector getSize() const { return _sprite->getSize(); }
            std::map<std::string, unsigned> getInventory() const { return _inventory; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            std::vector<Food> getFoods() const { return _food; }
            double getScaleRatio() const { return scaleRatio; }
            std::vector<std::shared_ptr<GUI::Trantorian>> getTrantorians() { return _trantorians; }
            std::vector<std::shared_ptr<GUI::Egg>> getEggs() { return _eggs; }
            std::shared_ptr<GUI::Trantorian> getTrantorian(unsigned id);
            std::shared_ptr<GUI::Egg> getEgg(unsigned id);
            Interface::Checkbox::State getState() const { return _state; }
            Interface::CALLBACK getCallback() const { return _callback; }

            void addFood(const std::string &food);
            void removeFood(std::string food);
            void addTrantorian(std::shared_ptr<GUI::Trantorian> trantorian) { _trantorians.push_back(trantorian); }
            void removeTrantorian(std::shared_ptr<GUI::Trantorian> trantorian);
            void addEgg(std::shared_ptr<GUI::Egg> egg) { _eggs.push_back(egg); }
            void removeEgg(std::shared_ptr<GUI::Egg> egg);
            void removeEggs() { _eggs.clear(); }

            void updateState(const Math::Vector &mousePos, const bool &mousePressed, int &userId, double scale) {
                auto size = _sprite->getSize();
                auto pos = _sprite->getPos();
                if (mousePos.x() >= pos.x() && mousePos.x() <= pos.x() + (size.x() * scale) &&
                    mousePos.y() >= pos.y() && mousePos.y() <= pos.y() + (size.y() * scale)) {
                    if (_state == Interface::Checkbox::State::IDLE)
                        _state = Interface::Checkbox::State::HOVER;
                    if (_state == Interface::Checkbox::State::CLICKED)
                        _state = Interface::Checkbox::State::RELEASED;
                    if (mousePressed)
                        _state = Interface::Checkbox::State::CLICKED;
                } else {
                    if (!mousePressed || _state == Interface::Checkbox::State::HOVER)
                        _state = Interface::Checkbox::State::IDLE;
                }
                _sprite->animate(_state);
            }

            void drawTile() { _sprite->drawSprite(); }
            void drawFoods();
            void drawTrantorians();
            void drawEggs();

        protected:
        private:
            std::shared_ptr<sf::RenderWindow> _window = nullptr;
            std::shared_ptr<ISprite> _sprite = nullptr;
            std::vector<Food> _food;
            std::vector<std::shared_ptr<GUI::Trantorian>> _trantorians;
            std::vector<std::shared_ptr<GUI::Egg>> _eggs;
            double scaleRatio = 0.2;
            std::map<std::string /* food name */, unsigned /* food quantity */> _inventory;
            Interface::Checkbox::State _state = Interface::Checkbox::State::IDLE;
            Interface::CALLBACK _callback = Interface::OPEN_INVENTORY_CASE;
    };
    std::ostream &operator<<(std::ostream &os, Tiles &tile);
} // namespace GUI

#endif /* !TILES_HPP_ */

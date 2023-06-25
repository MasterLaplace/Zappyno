/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Trantorian
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_
    #include "Egg.hpp"
    #include "ISprite.hpp"
    #include "CheckBox.hpp"
    #include "Vector.hpp"
    #include <memory>
    #include <map>

namespace GUI {
    class Trantorian {
        public:
            enum Direction {
                NORTH,
                EAST,
                SOUTH,
                WEST
            };
            enum State {
                IDLE,
                MOVING,
                EATING,
                TAKING,
                DROPPING,
                EXPULSING,
                BROADCASTING,
                INCANTING,
                FORKING,
                CONNECTING,
                DYING
            };

        public:
            Trantorian();
            ~Trantorian() = default;

            void setLevel(unsigned level) { _level = level; }
            void setId(unsigned id) { _id = id; }
            void setPos(Math::Vector pos) { _sprite->setPos(pos); }
            void setNextPos(Math::Vector pos) { _nextPos = pos; }
            void setNextPosId(int id) { _nextPosId = id; }
            void setScale(Math::Vector scale) { _sprite->setScale(scale); }
            void setDir(Direction dir) { _dir = dir; }
            void setTeam(std::string team) { _team = team; }
            void setFood(std::string food, unsigned quantity) { _inventory[food] = quantity; }
            void setInventory(std::map<std::string, unsigned> inventory) { _inventory = inventory; }
            void setState(State state) { _state = state; }
            void setSprite(std::shared_ptr<ISprite> sprite) { _sprite = sprite; }

            unsigned getLevel() const { return _level; }
            unsigned getId() const { return _id; }
            unsigned getSpeed() const { return _speed; }
            int getNextPosId() const { return _nextPosId; }
            unsigned getFood(std::string food) const { return _inventory.at(food); }
            Math::Vector getPos() const { return _sprite->getPos(); }
            Math::Vector getNextPos() const { return _nextPos; }
            Math::Vector getScale() const { return _sprite->getScale(); }
            Math::Vector getSize() const { return _sprite->getSize(); }
            Direction getDir() const { return _dir; }
            std::string getTeam() const { return _team; }
            std::map<std::string, unsigned> getInventory() const { return _inventory; }
            Interface::CALLBACK getCallback() const { return _callback; }
            Interface::Checkbox::State getCheckboxState() const { return _buttonState; }
            State getState() const { return _state; }

            Math::Vector getOriginalPos() { return _originalPos; }
            void setOriginalPos(Math::Vector pos) { _originalPos = pos; }

            double DirToRandian();

            std::string intToFoodString(unsigned type);

            void addFood(unsigned food, unsigned quantity) { _inventory[intToFoodString(food)] += quantity; }
            void removeFood(unsigned food, unsigned quantity) { _inventory[intToFoodString(food)] -= quantity; }

            Math::Vector calculDistance(Math::Vector pos, Math::Vector nextPos, unsigned speed, double scale);

            void updateTrantorianState(const Math::Vector &mousePos, const bool &mousePressed, int &userId, double scale);
            void animationTrantorian();
            void drawTrantorian() { _sprite->drawSprite(); }

        protected:
        private:
            unsigned _id;
            unsigned _level = 1;
            unsigned _speed = 1;
            int _nextPosId = -1;
            Math::Vector _nextPos;
            Math::Vector _originalPos;
            Direction _dir = NORTH;
            std::string _team;
            std::map<std::string /* food name */, unsigned /* food quantity */> _inventory;
            State _state = IDLE;
            std::shared_ptr<ISprite> _sprite = nullptr;
            Interface::Checkbox::State _buttonState = Interface::Checkbox::State::IDLE;
            Interface::CALLBACK _callback = Interface::OPEN_INVENTORY_USER;
    };
    std::ostream &operator<<(std::ostream &os, const Trantorian &trantorian);
    std::ostream &operator<<(std::ostream &os, const Trantorian::Direction &dir);
    std::ostream &operator<<(std::ostream &os, const Trantorian::State &state);
} // namespace GUI

#endif /* !TRANTORIAN_HPP_ */

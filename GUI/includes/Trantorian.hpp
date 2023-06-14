/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Trantorian
*/

#ifndef TRANTORIAN_HPP_
    #define TRANTORIAN_HPP_
    #include "Vector.hpp"
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
            void setPos(Math::Vector pos) { _pos = pos; _pos.z(_pos.y()), _pos.y(0); }
            void setDir(Direction dir) { _dir = dir; }
            void setTeam(std::string team) { _team = team; }
            void setInventory(std::map<std::string, unsigned> inventory) { _inventory = inventory; }
            void setState(State state) { _state = state; }

            unsigned getLevel() const { return _level; }
            unsigned getId() const { return _id; }
            Math::Vector getPos() const { return {_pos.x(), _pos.z()}; }
            Direction getDir() const { return _dir; }
            std::string getTeam() const { return _team; }
            std::map<std::string, unsigned> getInventory() const { return _inventory; }
            State getState() const { return _state; }

            double DirToRandian();

            static inline std::string intToFoodString(unsigned type);

            void addFood(unsigned food, unsigned quantity) { _inventory[intToFoodString(food)] += quantity; }
            void removeFood(unsigned food, unsigned quantity) { _inventory[intToFoodString(food)] -= quantity; }


        protected:
        private:
            unsigned _id;
            unsigned _level = 1;
            Direction _dir = NORTH;
            Math::Vector _pos;
            std::string _team;
            std::map<std::string /* food name */, unsigned /* food quantity */> _inventory;
            State _state = IDLE;
    };
    std::ostream &operator<<(std::ostream &os, const Trantorian &trantorian);
    std::ostream &operator<<(std::ostream &os, const Trantorian::Direction &dir);
    std::ostream &operator<<(std::ostream &os, const Trantorian::State &state);
} // namespace GUI

#endif /* !TRANTORIAN_HPP_ */

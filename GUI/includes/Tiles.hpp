/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Tiles
*/

#ifndef TILES_HPP_
    #define TILES_HPP_
    #include "Vector.hpp"
    #include <map>

namespace GUI {
    class Tiles {
        public:
            Tiles(Math::Vector pos, std::vector<unsigned> &inventory) : _pos(pos) {
                setInventory(inventory);
            }
            ~Tiles() = default;

            void setPos(Math::Vector pos) { _pos = pos; }
            void setInventory(std::vector<unsigned> &inventory) {
                _inventory["food"] = inventory[0];
                _inventory["linemate"] = inventory[1];
                _inventory["deraumere"] = inventory[2];
                _inventory["sibur"] = inventory[3];
                _inventory["mendiane"] = inventory[4];
                _inventory["phiras"] = inventory[5];
                _inventory["thystame"] = inventory[6];
            }

            Math::Vector getPos() const { return _pos; }
            std::map<std::string, unsigned> getInventory() const { return _inventory; }

        protected:
        private:
            Math::Vector _pos;
            std::map<std::string /* food name */, unsigned /* food quantity */> _inventory;
    };
} // namespace GUI

#endif /* !TILES_HPP_ */

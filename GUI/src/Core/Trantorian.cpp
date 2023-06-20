/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Trantorian
*/

#include "../../includes/Trantorian.hpp"

namespace GUI {
    Trantorian::Trantorian() {
        _inventory["food"] = 10;
        _inventory["linemate"] = 0;
        _inventory["deraumere"] = 0;
        _inventory["sibur"] = 0;
        _inventory["mendiane"] = 0;
        _inventory["phiras"] = 0;
        _inventory["thystame"] = 0;
    }

    double Trantorian::DirToRandian() {
        switch (_dir) {
            case NORTH:
                return 0;
            case EAST:
                return 90;
            case SOUTH:
                return 180;
            case WEST:
                return 270;
        }
        return (0);
    }

    std::string Trantorian::intToFoodString(unsigned type) {
        switch (type) {
            case 0:
                return "food";
            case 1:
                return "linemate";
            case 2:
                return "deraumere";
            case 3:
                return "sibur";
            case 4:
                return "mendiane";
            case 5:
                return "phiras";
            case 6:
                return "thystame";
        }
        return ("");
    }

    std::ostream &operator<<(std::ostream &os, const Trantorian &trantorian) {
        os << "id: " << trantorian.getId() << " (" << trantorian.getTeam() << ")" << std::endl;
        os << "level: " << trantorian.getLevel() << std::endl;
        os << "pos: " << trantorian.getPos() << std::endl;
        os << "dir: " << trantorian.getDir() << std::endl;
        os << "inventory: " << std::endl;
        for (auto &item : trantorian.getInventory())
            os << "\t" << item.first << ": " << item.second << std::endl;
        os << "state: " << trantorian.getState() << std::endl;
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Trantorian::Direction &dir) {
        switch (dir) {
            case Trantorian::NORTH:
                os << "NORTH";
                break;
            case Trantorian::EAST:
                os << "EAST";
                break;
            case Trantorian::SOUTH:
                os << "SOUTH";
                break;
            case Trantorian::WEST:
                os << "WEST";
                break;
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Trantorian::State &state) {
        switch (state) {
            case Trantorian::IDLE:
                os << "IDLE";
                break;
            case Trantorian::MOVING:
                os << "MOVING";
                break;
            case Trantorian::EATING:
                os << "EATING";
                break;
            case Trantorian::TAKING:
                os << "TAKING";
                break;
            case Trantorian::DROPPING:
                os << "DROPPING";
                break;
            case Trantorian::EXPULSING:
                os << "EXPULSING";
                break;
            case Trantorian::BROADCASTING:
                os << "BROADCASTING";
                break;
            case Trantorian::INCANTING:
                os << "INCANTING";
                break;
            case Trantorian::FORKING:
                os << "FORKING";
                break;
            case Trantorian::CONNECTING:
                os << "CONNECTING";
                break;
            case Trantorian::DYING:
                os << "DYING";
                break;
        }
        return os;
    }
}

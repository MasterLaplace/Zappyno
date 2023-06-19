/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Egg
*/

#ifndef EGG_HPP_
    #define EGG_HPP_
    #include "Vector.hpp"

namespace GUI {
    class Egg {
        public:
            Egg() = default;
            ~Egg() = default;

            void setId(unsigned id) { _id = id; }
            void setPos(Math::Vector pos) { _pos = pos; }
            void setTeam(std::string team) { _team = team; }

            unsigned getId() const { return _id; }
            Math::Vector getPos() const { return _pos; }
            std::string getTeam() const { return _team; }

        protected:
        private:
            unsigned _id;
            Math::Vector _pos;
            std::string _team;
    };
} // namespace GUI

#endif /* !EGG_HPP_ */

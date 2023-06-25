/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Egg
*/

#ifndef EGG_HPP_
    #define EGG_HPP_
    #include "Vector.hpp"
    #include "ISprite.hpp"
    #include <memory>

namespace GUI {
    class Egg {
        public:
            Egg(std::shared_ptr<ISprite> sprite) { _sprite = sprite; }
            ~Egg() = default;

            void setId(unsigned id) { _id = id; }
            void setTeam(std::string team) { _team = team; }

            Math::Vector getPos() { return _sprite->getPos(); }
            void setPos(Math::Vector pos) { _sprite->setPos(pos); }
            Math::Vector getOriginalPos() { return _originalPos; }
            void setOriginalPos(Math::Vector pos) { _originalPos = pos; }
            Math::Vector getSize() { return _sprite->getSize(); }
            void setSize(Math::Vector size) { _sprite->setSize(size); }
            Math::Vector getScale() { return _sprite->getScale(); }
            void setScale(Math::Vector scale) { _sprite->setScale(scale); }

            unsigned getId() const { return _id; }
            std::string getTeam() const { return _team; }

            void drawEgg() { _sprite->drawSprite(); }

        protected:
        private:
            std::shared_ptr<ISprite> _sprite = nullptr;
            unsigned _id;
            Math::Vector _originalPos;
            std::string _team;
    };
} // namespace GUI

#endif /* !EGG_HPP_ */

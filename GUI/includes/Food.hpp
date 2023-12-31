/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Food
*/

#ifndef FOOD_HPP_
    #define FOOD_HPP_
    #include <string>
    #include <memory>
    #include "Vector.hpp"
    #include "ISprite.hpp"

namespace GUI {
    class Food {
        public:
            enum class FoodType {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME,
                NONE
            };
        public:
            Food(const std::string &type, std::shared_ptr<ISprite> sprite) {
                _type = StringToFoodType(type);
                _sprite = sprite;
            }
            ~Food() = default;

            FoodType getType() const { return _type; }

            std::string getName() { return FoodTypeToString(_type); }

            Math::Vector getPos() { return _sprite->getPos(); }
            void setPos(Math::Vector pos) { _sprite->setPos(pos); }
            Math::Vector getOriginalPos() { return _originalPos; }
            void setOriginalPos(Math::Vector pos) { _originalPos = pos; }
            Math::Vector getSize() { return _sprite->getSize(); }
            void setSize(Math::Vector size) { _sprite->setSize(size); }
            Math::Vector getScale() { return _sprite->getScale(); }
            void setScale(Math::Vector scale) { _sprite->setScale(scale); }

            std::string FoodTypeToString(const FoodType &type) {
                switch (type) {
                    case FoodType::FOOD:
                        return "food";
                    case FoodType::LINEMATE:
                        return "linemate";
                    case FoodType::DERAUMERE:
                        return "deraumere";
                    case FoodType::SIBUR:
                        return "sibur";
                    case FoodType::MENDIANE:
                        return "mendiane";
                    case FoodType::PHIRAS:
                        return "phiras";
                    case FoodType::THYSTAME:
                        return "thystame";
                    default:
                        return "none";
                }
            }
            FoodType StringToFoodType(const std::string &type) {
                if (type == "food")
                    return FoodType::FOOD;
                if (type == "linemate")
                    return FoodType::LINEMATE;
                if (type == "deraumere")
                    return FoodType::DERAUMERE;
                if (type == "sibur")
                    return FoodType::SIBUR;
                if (type == "mendiane")
                    return FoodType::MENDIANE;
                if (type == "phiras")
                    return FoodType::PHIRAS;
                if (type == "thystame")
                    return FoodType::THYSTAME;
                return FoodType::NONE;
            }

            void drawFood() { _sprite->drawSprite(); }

        protected:
        private:
            std::shared_ptr<ISprite> _sprite = nullptr;
            Math::Vector _originalPos;
            FoodType _type;
    };
} // namespace GUI

#endif /* !FOOD_HPP_ */

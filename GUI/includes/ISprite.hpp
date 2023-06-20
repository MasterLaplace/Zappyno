/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** ISprite
*/

#ifndef ISPRITE_HPP_
    #define ISPRITE_HPP_
    #include "Vector.hpp"

class ISprite {
    public:
        virtual ~ISprite() = default;
        virtual void animate(const unsigned &state) = 0;
        virtual void animate_checkbox(bool &ischecked, const unsigned &state) = 0;
        virtual void setOffset(Math::Vector offset) = 0;
        virtual void setMaxOffsetX(unsigned max_offset_x) = 0;
        virtual void setPos(Math::Vector pos) = 0;
        virtual void setScale(Math::Vector scale) = 0;
        virtual void setOrigin(Math::Vector origin) = 0;
        virtual void setSize(Math::Vector size) = 0;
        virtual void setTransparency(const unsigned &transparency) = 0;
        virtual Math::Vector getPos() const = 0;
        virtual Math::Vector getScale() const = 0;
        virtual Math::Vector getOrigin() const = 0;
        virtual Math::Vector getSize() const = 0;
        virtual Math::Vector getMaxSize() const = 0;
        virtual unsigned getTransparency() const = 0;
        virtual void rotate(const float &angle) = 0;
        virtual void drawSprite() const = 0;
};

#endif /* !ISPRITE_HPP_ */

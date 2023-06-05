/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Bar
*/

#include "../../includes/Bar.hpp"

namespace Interface {
    void Bar::updateState()
    {
        Math::Vector rect = this->_sprite->getSize();
        auto max_size = this->_sprite->getMaxSize();
        unsigned percent = (*_actual * 100) / *_max;

        rect.x(percent * max_size.x() / 100);
        if (rect.x() <= 0)
            rect.x(1);
        this->_sprite->setSize(rect);
    }
}

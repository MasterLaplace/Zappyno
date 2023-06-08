/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Bar
*/

#ifndef BAR_HPP_
    #define BAR_HPP_
    #include "ISprite.hpp"
    #include <SFML/Graphics.hpp>
    #include <memory>

/**
 * @brief Bar class
 *
 * @namespace Interface
 * @example in SFML:
 * Interface::Bar bar = Interface::Bar(std::make_shared<Sf_sprite::SfSprite>(_window, "pathname.png", Math::Vector(0, 0), Math::Vector(1, 1)), true);
 * while (_window.isOpen()) {
 *      _bar.updateState(50, 100);
 *      _bar.drawBar();
 * }
 * @example in SDL: @deprecated description of the example in SDL is missing (see SFML example)
 * Interface::Bar bar = Interface::Bar(std::make_shared<Sdl_sprite::SdlSprite>(_window, "pathname.png", Math::Vector(0, 0), Math::Vector(1, 1)), true);
 * while (_window.isOpen()) {
 *     _bar.updateState(50, 100);
 *    _bar.drawBar();
 * }
 */
namespace Interface {
    class Bar {
        public:
            Bar() = default;
            Bar(std::shared_ptr<ISprite> sprite, bool isVertial = false) {
                _sprite = sprite;
                _pos = sprite->getPos();
                _size = sprite->getSize();
                _scale = sprite->getScale();
                if (isVertial) {
                    _sprite->rotate(-90);
                    _sprite->setPos({_pos.x(), _pos.y() + _size.x()});
                }
            }
            ~Bar() = default;

            void setBarState(std::shared_ptr<unsigned> actual, std::shared_ptr<unsigned> max) { _actual = actual, _max = max; }
            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setSize(const Math::Vector &size) { _size = size; }
            void setScale(const Math::Vector &scale) { _scale = scale; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            std::shared_ptr<unsigned> getActual() const { return _actual; }
            std::shared_ptr<unsigned> getMax() const { return _max; }
            void updateState();
            void drawBar() const { _sprite->drawSprite(); }

        protected:
        private:
            Math::Vector _pos;
            Math::Vector _size;
            Math::Vector _scale;
            std::shared_ptr<ISprite> _sprite;
            std::shared_ptr<unsigned> _actual = nullptr;
            std::shared_ptr<unsigned> _max = nullptr;
    };
} // namespace Interface

#endif /* !BAR_HPP_ */

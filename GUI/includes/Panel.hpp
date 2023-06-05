/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Panel
*/

#ifndef PANEL_HPP_
    #define PANEL_HPP_
    #include "Button.hpp"
    #include "Input.hpp"
    #include "Bar.hpp"

namespace Interface {
    class Panel {
        public:
            Panel() = default;
            Panel(std::shared_ptr<ISprite> sprite) {
                _sprite = sprite;
                _pos = sprite->getPos();
                _scale = sprite->getScale();
            }
            ~Panel() = default;

            void setPos(const Math::Vector &pos) { _pos = pos; }
            void setScale(const Math::Vector &scale) { _scale = scale; }
            void setDisplayed(const bool &isDisplayed) { _isDisplayed = isDisplayed; }
            std::shared_ptr<ISprite> getSprite() const { return _sprite; }
            bool isDisplayed() const { return _isDisplayed; }

            void addButton(const Interface::Button &button) { _buttons.push_back(button); }
            void addInput(const Interface::Input &input) { _inputs.push_back(input); }
            void addBar(const Interface::Bar &bar) { _bars.push_back(bar); }
            template<typename T>
            void drawPanel(T &win) {
                if (!_isDisplayed) return;
                if (_sprite) _sprite->drawSprite();
                for (auto &button : _buttons)
                    button.drawButton();
                for (auto &input : _inputs)
                    input.drawInput<T>(win);
                for (auto &bar : _bars)
                    bar.drawBar();
            }
            void updatePanel(const Math::Vector &mousePos, const bool &mousePressed = false);
            void updatePanel(const Math::Vector &mousePos, int key, const bool &mousePressed = false);

            Panel &operator=(const bool &displayed) {
                _isDisplayed = displayed;
                return *this;
            }

        protected:
        private:
            std::vector<Interface::Button> _buttons;
            std::vector<Interface::Input> _inputs;
            std::vector<Interface::Bar> _bars;
            std::shared_ptr<ISprite> _sprite;
            Math::Vector _pos;
            Math::Vector _scale;
            bool _isDisplayed = true;
    };
} // namespace Interface

#endif /* !PANEL_HPP_ */

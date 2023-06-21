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
    #include "CheckBox.hpp"
    #include "Bar.hpp"
    #include "Chat.hpp"

/**
 * @brief Panel class
 *
 * @namespace Interface
 * @example in SFML:
 * Interface::Panel _panel = Interface::Panel(std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/table.png", Math::Vector(0, 0), Math::Vector(0.75, 0.75)));
 * auto _button = Interface::Button(std::make_shared<Sf_sprite::SfSprite>(_window, "GUI/assets/play_button-removebg-preview.png", Math::Vector(0, 0), Math::Vector(1, 1)));
 * auto sprite = _button.getSprite();
 * sprite->setOffset(Math::Vector(251, 249));
 * sprite->setMaxOffsetX(1);
 * _panel.addButton(_button);
 * while (_window.isOpen()) {
 *      _button.updatePanel(sf::Mouse::getPosition(window), event.key.code, sf::Mouse::isButtonPressed(sf::Mouse::Left));
 *      _button.drawPanel<sf::RenderWindow>(window);
 * }
 */
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
            void setType(const std::string &type) { _type = type; }
            void setCallback(const Interface::CALLBACK &callback) { _callback = callback; }

            std::string getType() const { return _type; }

            std::shared_ptr<Interface::Chat> getChat() const { return _chat; }

            void addButton(const Interface::Button &button) { _buttons.push_back(button); }
            void addInput(const Interface::Input &input) { _inputs.push_back(input); }
            void addCheckbox(const Interface::Checkbox &checkbox) { _checkboxs.push_back(checkbox); }
            void addBar(const Interface::Bar &bar) { _bars.push_back(bar); }
            void addChat(const Interface::Chat &chat) { _chat = std::make_shared<Interface::Chat>(chat); }
            template<typename Win>
            void drawPanel(Win &win) {
                if (!_isDisplayed || (_callback == NONE && _type == "inventory")) return;
                if (_sprite) { _sprite->drawSprite(); }
                for (auto &button : _buttons)
                    button.drawButton();
                for (auto &checkbox : _checkboxs)
                    checkbox.drawCheckbox();
                for (auto &input : _inputs)
                    input.drawInput<Win>(win);
                for (auto &bar : _bars)
                    bar.drawBar();
                if (_chat)
                    _chat->drawChat<Win>(win);
            }
            void updatePanel(const Math::Vector &mousePos, const bool &mousePressed = false);
            void updatePanel(const Math::Vector &mousePos, int key, const bool &mousePressed = false);
            std::vector<CALLBACK> getCallback();

            Panel &operator=(const bool &displayed) { _isDisplayed = displayed; return *this; }

        protected:
        private:
            std::vector<Interface::Button> _buttons;
            std::vector<Interface::Checkbox> _checkboxs;
            std::vector<Interface::Input> _inputs;
            std::vector<Interface::Bar> _bars;
            std::shared_ptr<Interface::Chat> _chat = nullptr;
            std::shared_ptr<ISprite> _sprite = nullptr;
            Math::Vector _pos;
            Math::Vector _scale;
            bool _isDisplayed = true;
            Interface::CALLBACK _callback = NONE;
            std::string _type;
    };
} // namespace Interface

#endif /* !PANEL_HPP_ */

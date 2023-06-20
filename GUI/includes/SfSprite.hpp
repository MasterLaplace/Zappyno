/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SfSprite
*/

#ifndef SFSPRITE_HPP_
    #define SFSPRITE_HPP_
    #include <SFML/Graphics.hpp>
    #include "ISprite.hpp"
    #include <memory>

/**
 * @brief SfSprite class
 *
 * @namespace Interface
 * @example in SFML:
 * Sf_sprite::SfSprite sprite = Sf_sprite::SfSprite(window, "pathname.png", Math::Vector(0, 0), Math::Vector(1, 1));
 * while (_window.isOpen()) {
 *      sprite.drawSprite();
 * }
 */
namespace Sf_sprite {
    class SfSprite : public ISprite {
        public:
        sf::Texture texture;
        sf::Vector2f pos;
        sf::Vector2f scale;
        sf::Vector2f origin;
        sf::Sprite sprite;
        sf::IntRect maxSize;
        std::shared_ptr<sf::RenderWindow> window;
        // Animation
        unsigned offset_x = 0;
        unsigned offset_y = 0;
        unsigned max_offset_x = 0;

        void setOffset(Math::Vector offset) override;
        void setMaxOffsetX(unsigned max_offset_x) { this->max_offset_x = max_offset_x; }
        void setPos(Math::Vector pos) override { this->pos = sf::Vector2f(pos.x(), pos.y()); sprite.setPosition(this->pos); }
        void setScale(Math::Vector scale) override { this->scale = sf::Vector2f(scale.x(), scale.y()); }
        void setOrigin(Math::Vector origin) override { this->origin = sf::Vector2f(origin.x(), origin.y()); }
        void setSize(Math::Vector size) override { this->sprite.setTextureRect(sf::IntRect(0, 0, size.x(), size.y())); }
        void setTransparency(const unsigned &transparency) override;
        Math::Vector getPos() const override { return Math::Vector(this->pos.x, this->pos.y); }
        Math::Vector getScale() const override { return Math::Vector(this->scale.x, this->scale.y); }
        Math::Vector getOrigin() const override { return Math::Vector(this->origin.x, this->origin.y); }
        Math::Vector getSize() const override { return Math::Vector(this->sprite.getTextureRect().width, this->sprite.getTextureRect().height); }
        Math::Vector getMaxSize() const override { return Math::Vector(this->maxSize.width, this->maxSize.height); }
        unsigned getTransparency() const override { return this->sprite.getColor().a; }

        void rotate(const float &angle) override { this->sprite.setRotation(angle); }

        SfSprite(std::shared_ptr<sf::RenderWindow> &win, const std::string &pathname, Math::Vector pos, Math::Vector scale, Math::Vector origin = {0, 0});

        void animate(const unsigned &state = 0) {
            sf::IntRect rect = this->sprite.getTextureRect();
            unsigned end = this->offset_x * (this->max_offset_x - 1);

            rect.left += this->offset_x;
            rect.top = this->offset_y * state;
            this->sprite.setTextureRect(rect);
            if (rect.left >= int(end)) {
                rect.left = 0;
                this->sprite.setTextureRect(rect);
            }
        }

        void animate_checkbox(bool &ischecked, const unsigned &state = 0) {
            sf::IntRect rect = this->sprite.getTextureRect();

            rect.left = this->offset_x * ischecked;
            rect.top = this->offset_y * state;
            this->sprite.setTextureRect(rect);
        }
        void drawSprite() const override { this->window->draw(this->sprite); }
    };

    void update(SfSprite &sprite);
    sf::Sprite createSprite(SfSprite &sprite);

} // namespace Sf_sprite

#endif /* !SFSPRITE_HPP_ */

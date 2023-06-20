/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SfSprite
*/

#include "../../../../includes/SfSprite.hpp"

namespace Sf_sprite {
    SfSprite::SfSprite(std::shared_ptr<sf::RenderWindow> &win, const std::string &pathname, Math::Vector pos, Math::Vector scale, Math::Vector origin) {
        sf::Texture texture;
        this->window = win;
        texture.loadFromFile(pathname);
        this->texture = texture;
        auto size = this->texture.getSize();
        this->maxSize = sf::IntRect(0, 0, size.x, size.y);
        this->pos = sf::Vector2f(pos.x(), pos.y());
        this->scale = sf::Vector2f(scale.x(), scale.y());
        this->origin = sf::Vector2f(origin.x(), origin.y());
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(this->pos);
        this->sprite.setScale(this->scale);
        this->sprite.setOrigin(this->origin);
    }

    void SfSprite::setTransparency(const unsigned &transparency) {
        auto color = this->sprite.getColor();
        color.a = transparency;
        this->sprite.setColor(color);
    }

    void SfSprite::setOffset(Math::Vector offset) {
        this->offset_x = offset.x();
        this->offset_y = offset.y();
        this->sprite.setTextureRect(sf::IntRect(0, 0, offset.x(), offset.y()));
    }

    void SfSprite::animate(const unsigned &state) {
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

    void SfSprite::animate_checkbox(bool &ischecked, const unsigned &state) {
        sf::IntRect rect = this->sprite.getTextureRect();

        rect.left = this->offset_x * ischecked;
        rect.top = this->offset_y * state;
        this->sprite.setTextureRect(rect);
    }

    void update(SfSprite &sprite) {
        sprite.sprite.setPosition(sprite.pos);
        sprite.sprite.setScale(sprite.scale);
        sprite.sprite.setOrigin(sprite.origin);
    }

    sf::Sprite createSprite(SfSprite &sprite) {
        sprite.sprite.setTexture(sprite.texture);
        sprite.sprite.setPosition(sprite.pos);
        sprite.sprite.setScale(sprite.scale);
        sprite.sprite.setOrigin(sprite.origin);
        return sprite.sprite;
    }
} // namespace Sf_sprite

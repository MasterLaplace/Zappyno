/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** SfSprite
*/

#include "../../../../includes/SfSprite.hpp"

namespace Sf_sprite {
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

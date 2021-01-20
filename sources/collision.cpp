#include "../headers/collision.hpp"
#include "../headers/tile.hpp"

bool Collision::isSpriteColliding(
    const sf::Sprite& target,
    const std::vector<Tile>& surroundings
) const {
    for (const auto& tile : surroundings) {
        if (target.getGlobalBounds().intersects(tile.getBounds())) {
            return true;
        }
    }
    return false;
}

bool Collision::isSpriteColliding(
    sf::Sprite sprite1,
    float scale1,
    sf::Sprite sprite2,
    float scale2
) const {
    sprite1.setScale(scale1, scale2);
    sprite2.setScale(scale2, scale1);
    return isSpriteColliding(sprite1, sprite2);
}

bool Collision::isSpriteColliding(
    sf::Sprite target,
    float targetScale,
    const std::vector<sf::Sprite>& surroundings,
    float surroundingScale
) const {
    for (auto sprite : surroundings) {
        target.setScale(targetScale, surroundingScale);
        sprite.setScale(surroundingScale, targetScale);

        if (isSpriteColliding(sprite, target)) {
            return true;
        }
    }
    return false;
}

bool Collision::isSpriteColliding(
    const sf::Sprite& target,
    const std::vector<sf::Sprite>& surroundings
) const {
    for (auto const& sprite : surroundings) {
        if (isSpriteColliding(sprite, target)) {
            return true;
        }
    }
    return false;
}

bool Collision::isSpriteColliding(
    const sf::Sprite& sprite1,
    const sf::Sprite& sprite2
) const {
    return isBoundsColliding(
        sprite1.getGlobalBounds(),
        sprite2.getGlobalBounds()
    );
}

bool Collision::isBoundsColliding(
    const sf::FloatRect& bounds1,
    const sf::FloatRect& bounds2
) const {
    return bounds1.intersects(bounds2);
}

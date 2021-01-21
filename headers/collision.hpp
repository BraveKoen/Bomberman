#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__

#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.hpp"

class Collision {
public:
    Collision() = default;
    bool isSpriteColliding(
        const sf::Sprite& target,
        const std::vector<Tile>& surroundings
    ) const;
    bool isSpriteColliding(
        sf::Sprite sprite1,
        float scale1,
        sf::Sprite sprite2,
        float scale2
    ) const;
    bool isSpriteColliding(
        sf::Sprite target,
        float targetScale,
        const std::vector<sf::Sprite>& surroundings,
        float surroundingScale
    ) const;
    bool isSpriteColliding(
        const sf::Sprite& target,
        const std::vector<sf::Sprite>& surroundings
    ) const;
    bool isSpriteColliding(
        const sf::Sprite& sprite1,
        const sf::Sprite& sprite2
    ) const;
    bool isBoundsColliding(
        const sf::FloatRect& bounds1,
        const sf::FloatRect& bounds2
    ) const;   
};

#endif // __COLLISION_HPP__

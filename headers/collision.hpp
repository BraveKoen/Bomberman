#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__

#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.hpp"

class Collision {
public:
    Collision() = default;

    /// \brief
    ///  bool isSpriteColliding sf::Sprite, std::vector<Tile>
    /// \details
    /// this function will loop through all given tiles and checks if there is a collition
    /// when there is a collition is returns true
    bool isSpriteColliding(
        const sf::Sprite& target,
        const std::vector<Tile>& surroundings
    ) const;

    /// \brief
    ///  bool isSpriteColliding sf::Sprite, float, sf::Sprite, float
    /// \details
    /// the float is for the scale.
    /// when you rescale a sprite you have to give the scale value with it.
    /// otherwise the hitbox is not correct
    bool isSpriteColliding(
        sf::Sprite sprite1,
        float scale1,
        sf::Sprite sprite2,
        float scale2
    ) const;

    /// \brief
    ///  bool isSpriteColliding sf::Sprite, float, std::vector<sf::Sprite>, float
    /// \details
    /// the float is for the scale.
    /// when you rescale a sprite you have to give the scale value with it.
    /// otherwise the hitbox is not correct
    /// it will loop through all the sprites and returns true if there is a collition
    bool isSpriteColliding(
        sf::Sprite target,
        float targetScale,
        const std::vector<sf::Sprite>& surroundings,
        float surroundingScale
    ) const;

     /// \brief
    ///  bool isSpriteColliding, std::vector<sf::Sprite>
    /// \details
    /// it will loop through all the sprites in the vector and returns true if there is a collition
    bool isSpriteColliding(
        const sf::Sprite& target,
        const std::vector<sf::Sprite>& surroundings
    ) const;

    /// \brief
    ///  bool isSpriteColliding sf::Sprite, sf::Sprite
    /// \details
    /// returns true if the sprites collites
    bool isSpriteColliding(
        const sf::Sprite& sprite1,
        const sf::Sprite& sprite2
    ) const;

    /// \brief
    ///  bool isSpriteColliding sf::FloatRect, sf::FloatRect
    /// \details
    /// when the 2 sf::FloatRect collites it returns true
    bool isBoundsColliding(
        const sf::FloatRect& bounds1,
        const sf::FloatRect& bounds2
    ) const;   
};

#endif // __COLLISION_HPP__

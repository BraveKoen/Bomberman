#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "bombHandler.hpp"

class Character {
public:
    Character() = default;

    virtual void draw() = 0;

    virtual void setHealth(uint8_t health) = 0;
    virtual int getHealth() const = 0;
    
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual const sf::Vector2f& getPosition() const = 0;

    virtual void setMovementSpeed(uint8_t speed) = 0;
    virtual int getMovementSpeed() const = 0;
};

#endif // __CHARACTER_HPP__
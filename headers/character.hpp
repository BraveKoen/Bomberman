#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>

class Character{
public:
    Character(GameDataRef data){}
    ~Character(){}

private:

    virtual void draw() = 0;

    virtual void setHealth(uint8_t health) = 0;
    virtual int getHealth() = 0;
    
    virtual void setPosition(sf::Vector2f pos) = 0;
    virtual sf::Vector2f getPosition() = 0;

    virtual void setMovementSpeed(uint8_t speed) = 0;
    virtual int getMovementSpeed() = 0;
};

#endif // __CHARACTER_HPP__
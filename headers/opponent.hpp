#ifndef __OPPONENT_HPP__
#define __OPPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "character.hpp"

class Opponent : public Character{
public:
    Opponent(gameDataRef data);
    ~Opponent();

    void draw() override;

    void setHealth(uint8_t health) override;
    int getHealth() override;

    void setPosition(sf::Vector2f pos) override;
    sf::Vector2f getPosition() override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() override;

private:
    gameDataRef data;

    sf::Sprite opponentSprite;
    sf::Vector2f opponentPosition;
    uint16_t movementSpeed = 2;
    uint8_t opponentHealth = 100;
};

#endif // __OPPONENT_HPP__

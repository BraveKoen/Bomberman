#ifndef __OPPONENT_HPP__
#define __OPPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "character.hpp"

class Opponent : public Character{
public:
    Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, const sf::Vector2f& spawnPosition);
    // ~Opponent();

    void draw() override;

    void setHealth(uint8_t health) override;
    int getHealth() const override;

    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f& getPosition() const override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() const override;

private:
    gameDataRef data; //the data
    std::shared_ptr<BombHandler> bombHandler;
    sf::Sprite opponentSprite;
    sf::Vector2f opponentPosition;
    uint16_t movementSpeed = 2;
    uint8_t opponentHealth = 100;
};

#endif // __OPPONENT_HPP__

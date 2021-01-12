#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "character.hpp"

class Player : public Character{
public:
    Player(gameDataRef data);
    ~Player();

    void draw() override;

    void setHealth(uint8_t health) override;
    int getHealth() override;

    void setPosition(sf::Vector2f pos) override;
    sf::Vector2f getPosition() override;

    void setMovementSpeed(uint8_t speed) override;
    int getMovementSpeed() override;

    sf::Sprite getSprite(){return playerSprite;};

    void playerMove(sf::Keyboard::Key key);

private:

    gameDataRef data;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    uint16_t movementSpeed = 2;
    uint8_t playerHealth = 100;
};

#endif // __PLAYER_HPP__
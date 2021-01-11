#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player{
public:
    Player(GameDataRef data);
    ~Player();

    void draw();
    void playerMove(sf::Keyboard::Key key);

private:

    GameDataRef data;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    uint16_t movementSpeed = 2;
};
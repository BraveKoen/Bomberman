#pragma once

#include <SFML/Graphics.hpp>

class Player{
public:
    Player(GameDataRef data);
    ~Player();

    void draw();

private:

    GameDataRef data;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    

};
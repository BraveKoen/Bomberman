#pragma once

#include <SFML/Graphics.hpp>

class Player{
public:
    Player(GameDataRef data);
    ~Player();

    void draw();
    void playerMove(bool up, bool down, bool right, bool left);

private:

    GameDataRef data;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
};
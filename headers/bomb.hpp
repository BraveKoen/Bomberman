#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
#include "../AnimatedSpriteLib/AnimatedSprite.hpp"

class Bomb{
public:
    Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos);
    ~Bomb(){std::cout << "Bomb Gone!" << std::endl;}

    void draw();

    void explode();

    bool isExploded(float currentTime);

    int getBombId();

    bool playerHit();

private:

    gameDataRef data;
    int id; // playerId who placed it

    int lenghtX; //How big is the explotion in x 
    int lenghtY;//How big is the explotion in y

    float explodeTime; //How many seconds does it need to explode
    float timeCreated; //When is the bomb placed

    sf::Sprite bombSprite;
    sf::Vector2f bombPosition;
    Animation fuse;
    Animation* currentAnimation;
    AnimatedSprite animatedSprite;
};

#endif // __BOMB_HPP__

#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "game.hpp"

class Bomb{
public:
    Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos);
    ~Bomb(){std::cout << "Bomb Gone!" << std::endl;}

    void draw();

    void explode();

    bool isExploded(float currentTime);

    int getBombId();

    bool playerHit();

    void setPos(sf::Vector2f pos);

    void clearBomb();

    void animateFuse();

private:

    gameDataRef data;
    int id; // playerId who placed it

    int lengthX; //How big is the explotion in x 
    int lengthY;//How big is the explotion in y

    float explodeTime; //How many seconds does it need to explode
    float timeCreated; //When is the bomb placed

    sf::Sprite bombSprite;
    sf::Vector2f bombPosition;

    std::vector<sf::Vector2u> destroyedTiles;
    bool explodeAnimation = false;
    bool isDone = false;

    std::vector<sf::Texture> bombFuseAnimation;
    unsigned int bombFuseAnimationIterator;
    sf::Clock clock;    
};

#endif // __BOMB_HPP__

#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
#include "tile.hpp"
#include "collision.hpp"

class Bomb{
public:
    Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos);
    ~Bomb(){}

    void draw();

    void explode();

    bool isExploded(float currentTime);

    int getBombId();

    bool playerHit();

    void setPos(sf::Vector2f pos);

    void clearBomb();

    bool bombColliding(const sf::Sprite& target);

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

    bool isDone = false;

};

#endif // __BOMB_HPP__

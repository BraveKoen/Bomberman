#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include <SFML/Graphics.hpp>

class Bomb{
public:
    Bomb(GameDataRef data, int playerId, int lenghtX, int lenghtY, int explodeTime,sf::Time timeCreated, sf::Vector2f pos);
    ~Bomb(){}

    void draw();

    void explode();

    bool explodeTime(sf::Time currentTime);

    int getBombId();

    bool playerHit();

private:

GameDataRef data;
int id; // playerId who placed it

int lenghtX; //How big is the explotion in x 
int lenghtY;//How big is the explotion in y

int explodeTime; //How many seconds does it need to explode
sf::Time timeCreated; //When is the bomb placed

sf::Sprite bombSprite;
sf::Vector2f bombPosition;

};

#endif // __BOMB_HPP__

#ifndef __BOMBHANDLER_HPP__
#define __BOMBHANDLER_HPP__

#include <vector>
#include <iostream> 
#include <memory> 

#include "bomb.hpp"


class BombHandler{
public:
    BombHandler(gameDataRef data);
    ~BombHandler(){}

    void createBomb(int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Vector2f pos);

    void draw();

    void update();

private:

    std::vector<std::unique_ptr<Bomb>> bombs;

    gameDataRef data;

    sf::Clock clock;
};

#endif // __BOMBMANAGER_HPP__

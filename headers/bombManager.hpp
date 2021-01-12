#ifndef __BOMBMANAGER_HPP__
#define __BOMBMANAGER_HPP__

#include <vector>
#include <iostream> 
#include <memory> 

#include "bomb.hpp"

class BombManager{
public:
    BombManager(GameDataRef data);
    ~BombManager(){}

private:

    void placeBomb(int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Vector2f pos); //!!!!! heb bij GameDataRef ergens een clock nodig die start bij het begin van de game

    void draw();
    
    std::vector<std::unique_ptr<Bomb>> bombs;

    GameDataRef data;
};

#endif // __BOMBMANAGER_HPP__

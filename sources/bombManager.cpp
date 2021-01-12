#include "../headers/bombManager.hpp"


BombManager::BombManager(GameDataRef data){
    
}

void BombManager::placeBomb(int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Vector2f pos){
    bombs.push_back(std::make_unique<Bomb>(data, playerId, lenghtX, lenghtY, explodeTime, pos));
    
}

void draw(){
    for(auto i : *bombs){
        if(!i->explodeTime()){
            i->draw();
        }else{
            i->explode();
        }
    }
}
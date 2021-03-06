#include "../headers/bombHandler.hpp"


BombHandler::BombHandler(gameDataRef data):
    data(data)
{}

void BombHandler::createBomb(int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Vector2f pos){
    bombs.push_back(std::make_unique<Bomb>(data, playerId, lenghtX, lenghtY, explodeTime, clock.getElapsedTime().asSeconds(), pos));
}

void BombHandler::draw(){
    //std::cout << clock.getElapsedTime().asSeconds() << std::endl;
    for(auto &bomb : bombs){
        bomb->draw();
    }
}

void BombHandler::update(){
    int count = 0;
    for(auto &bomb : bombs){
        if(bomb->isExploded(clock.getElapsedTime().asSeconds())){
            bombs.erase(bombs.begin() + count);
            break;
        }
        if(bomb->getPrimed()){
            bomb->animateExplosion();
            count++;
        }else{
            bomb->animateFuse();
            count++;
        }
    }
}

bool BombHandler::checkBombCollision(const sf::Sprite& target){
    for(auto &bomb : bombs){
        if(bomb->bombColliding(target)){
            return true;
        }
    }
    return false;
}
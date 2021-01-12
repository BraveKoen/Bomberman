#include "../headers/bomb.hpp"


Bomb::Bomb(GameDataRef data, int playerId, int lenghtX, int lenghtY, int explodeTime, sf::Time timeCreated, sf::Vector2f pos):
    data(data),
    id(playerId),
    lenghtX(lenghtX),
    lenghtY(lenghtY),
    explodeTime(explodeTime),
    timeCreated(timeCreated),
    bombPosition(pos)
{
    bombSprite.setTexture(data->getTexture("bomb.png"));
}

void Bomb::draw(){
    data->window.draw(bombSprite);
}

void Bomb::explode() {
    //explode animation
}

bool Bomb::explodeTime(sf::Time currentTime){
    if(timeCreated.asSeconds() + explodeTime > currentTime.asSeconds()){
        return false;
    }
    return true;
    
}

int Bomb::getBombId(){
    return id;
}

bool Bomb::playerHit(){
    //collition 
}

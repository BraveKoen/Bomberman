#include "../headers/bomb.hpp"

Bomb::Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos):
    data(data),
    id(playerId),
    lenghtX(lenghtX),
    lenghtY(lenghtY),
    explodeTime(explodeTime),
    timeCreated(timeCreated),
    bombPosition(pos)
{
    bombSprite.setTexture(data->assetManager.getTexture("Dynamite"));
    bombSprite.setScale(0.2, 0.2);
    bombSprite.setPosition(pos);
}

void Bomb::draw(){
    data->window.draw(bombSprite);
}

void Bomb::explode() {
    //explode animation
}

bool Bomb::isExploded(float currentTime){
    if(timeCreated + explodeTime > currentTime){
         return false;
     }
    return true;
}

int Bomb::getBombId(){
    return id;
}

bool Bomb::playerHit(){
    return false;
}

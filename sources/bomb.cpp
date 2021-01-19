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
    bombSprite.setTexture(data->assetManager.getTexture("Bomb"));
    bombSprite.setScale(0.2, 0.2);
    bombSprite.setPosition(pos);

    fuse.setSpriteSheet(data->assetManager.getTexture("Bomb"));
    fuse.addFrame(sf::IntRect(0, 0, 450, 375));
    fuse.addFrame(sf::IntRect(450, 0, 450, 375));
    fuse.addFrame(sf::IntRect(0, 375, 450, 375));
    fuse.addFrame(sf::IntRect(450, 0, 450, 375));

    currentAnimation = &fuse;
    animatedSprite.setPosition(bombPosition);
    animatedSprite.play(*currentAnimation);
}

void Bomb::draw(){
    data->window.draw(animatedSprite);
    animatedSprite.update(sf::seconds(1000.0f));
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

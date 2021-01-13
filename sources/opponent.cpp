#include "..//headers//opponent.hpp"


Opponent::Opponent(gameDataRef data):
    Character(data),
    data(data)
    {
        opponentSprite.setTexture(data->assetManager.getTexture("opponent.png"));  
    }


void Opponent::draw(){
    data->window.draw(opponentSprite);
}

void Opponent::setHealth(uint8_t health){
    opponentHealth = health;   
}

int Opponent::getHealth(){
    return opponentHealth;
}

void Opponent::setPosition(sf::Vector2f pos){
    opponentPosition = pos;
}

sf::Vector2f Opponent::getPosition(){
    return opponentPosition;
}

void Opponent::setMovementSpeed(uint8_t speed){
    movementSpeed = speed;
}

int Opponent::getMovementSpeed(){
    return movementSpeed;
}

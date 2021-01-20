#include "../headers/opponent.hpp"

Opponent::Opponent(gameDataRef data):
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

int Opponent::getHealth() const {
    return opponentHealth;
}

void Opponent::setPosition(const sf::Vector2f& pos){
    opponentPosition = pos;
}

const sf::Vector2f& Opponent::getPosition() const {
    return opponentPosition;
}

void Opponent::setMovementSpeed(uint8_t speed){
    movementSpeed = speed;
}

int Opponent::getMovementSpeed() const {
    return movementSpeed;
}

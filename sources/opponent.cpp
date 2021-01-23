#include "../headers/opponent.hpp"

Opponent::Opponent(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, sf::Vector2f spawnPosition):
    data(data),
    bombHandler(bombHandler),
    opponentPosition(spawnPosition)
{
    opponentSprite.setTexture(data->assetManager.getTexture("player4"));
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    opponentSprite.setScale(tileSize / data->assetManager.getTexture("player4").getSize().x / 2, tileSize / data->assetManager.getTexture("player4").getSize().y / 2);
    opponentSprite.setOrigin(data->assetManager.getTexture("player4").getSize().x / 2, data->assetManager.getTexture("player4").getSize().y / 2); 
    opponentSprite.setPosition(sf::Vector2f{150,150});
    opponentSprite.setPosition(spawnPosition);
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
    opponentSprite.setPosition(pos);
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

void Opponent::spawnBomb(int playerId){
    bombHandler->createBomb(playerId, 4, 4, 2, opponentPosition);
}

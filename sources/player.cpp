#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler):
    data(data),
    bombHandler(bombHandler)
{
    //playerSprite.setTexture(data->getTexture("player.png"));
    playerSprite.setTexture(data->assetManager.getTexture("Player"));
    playerSprite.setScale(0.2, 0.2);
}

void Player::draw() {
    data->window.draw(playerSprite);
}


void Player::setHealth(uint8_t health){
    playerHealth = health;
}

int Player::getHealth(){
    return playerHealth;
}

void Player::setPosition(sf::Vector2f pos){
    playerSprite.setPosition(pos);
}

sf::Vector2f Player::getPosition(){
    return playerPosition;
}

void Player::setMovementSpeed(uint8_t speed) {
    movementSpeed = speed;   
}

int Player::getMovementSpeed(){
    return movementSpeed;
}


void Player::playerMove(sf::Keyboard::Key key) {
    if(sf::Keyboard::Key::Up == key){
        playerPosition.y -= movementSpeed;
    }else if (sf::Keyboard::Key::Down == key){
        playerPosition.y += movementSpeed;
    }else if (sf::Keyboard::Key::Right == key){
        playerPosition.x += movementSpeed;
    }else if (sf::Keyboard::Key::Left == key){
        playerPosition.x -= movementSpeed;
    }
    if(sf::Keyboard::Key::Space == key){
        bombHandler->createBomb(playerId, 12, 12, 5, playerPosition);
        
    }
    playerSprite.setPosition(playerPosition);
}

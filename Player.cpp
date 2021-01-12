#include "Player.hpp"

Player::Player(GameDataRef data):
    Character(data),
    data(data)
    {
        playerSprite.setTexture(data->getTexture("player.png"));
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
        birdPosition.y -= movementSpeed;
    }else if (sf::Keyboard::Key::Down == key){
        birdPosition.y += movementSpeed;
    }else if (sf::Keyboard::Key::Right == key){
        birdPosition.x += movementSpeed;
    }else if (sf::Keyboard::Key::Left == key){
        birdPosition.x -= movementSpeed;
    }
    playerSprite.setPosition(birdPosition);
	}
}


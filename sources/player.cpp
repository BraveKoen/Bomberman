#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys):
    data(data),
    bombHandler(bombHandler),
    arrowKeys(arrowKeys)
    {
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


void Player::playerMove(){
    if(arrowKeys){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            playerPosition.y -= movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            playerPosition.y += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            playerPosition.x += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            playerPosition.x -= movementSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)){
            bombHandler->createBomb(playerId, 12, 12, 1, playerPosition);   
        }

    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            playerPosition.y -= movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            playerPosition.y += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            playerPosition.x += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            playerPosition.x -= movementSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            bombHandler->createBomb(playerId, 12, 12, 1, playerPosition);   
        }
    }



    playerSprite.setPosition(playerPosition);
	}


#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys):
    data(data),
    bombHandler(bombHandler),
    arrowKeys(arrowKeys)
{
    playerSprite.setTexture(data->assetManager.getTexture("Player"));
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    playerSprite.setScale(tileSize / data->assetManager.getTexture("Player").getSize().x, tileSize / data->assetManager.getTexture("Player").getSize().y);
    playerSprite.setOrigin(data->assetManager.getTexture("Player").getSize().x / 2, data->assetManager.getTexture("Player").getSize().y / 2);
}

void Player::draw() {
    data->window.draw(playerSprite);
}

void Player::update(){
    if(bombCooldown){
        if((timeBombPlaced + 5) <= clock.getElapsedTime().asSeconds()){
            bombCooldown = false;
        }
    }
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) && !bombCooldown){
            bombHandler->createBomb(playerId, 4, 4, 2, playerPosition); 
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bombCooldown){
            bombHandler->createBomb(playerId, 4, 4, 2, playerPosition);   
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
        }
    }
    playerSprite.setPosition(playerPosition);
}

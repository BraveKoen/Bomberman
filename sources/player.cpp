#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys, sf::Vector2f spawnPosition):
    data(data),
    bombHandler(bombHandler),
    arrowKeys(arrowKeys),
    playerPosition(spawnPosition)
{
    playerSprite.setTexture(data->assetManager.getTexture("player"));
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    playerSprite.setScale(tileSize / data->assetManager.getTexture("player").getSize().x, tileSize / data->assetManager.getTexture("player").getSize().y);
    playerSprite.setOrigin(data->assetManager.getTexture("player").getSize().x / 2, data->assetManager.getTexture("player").getSize().y / 2);
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
            prevPosition = playerPosition;
            playerPosition.y -= movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            prevPosition = playerPosition;
            playerPosition.y += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            prevPosition = playerPosition;
            playerPosition.x += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            prevPosition = playerPosition;
            playerPosition.x -= movementSpeed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) && !bombCooldown){
            bombHandler->createBomb(playerId, 4, 4, 2, playerPosition); 
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
        }
    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            prevPosition = playerPosition;
            playerPosition.y -= movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            prevPosition = playerPosition;
            playerPosition.y += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            prevPosition = playerPosition;
            playerPosition.x += movementSpeed;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            prevPosition = playerPosition;
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

void Player::revertMove() {
    playerPosition = prevPosition;
    playerSprite.setPosition(playerPosition);
}

#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys, const sf::Vector2f& spawnPosition):
    data{data},
    bombHandler{bombHandler},
    arrowKeys{arrowKeys},
    playerPosition{spawnPosition}
{
    playerSprite.setTexture(data->assetManager.getTexture("player"));
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    playerSprite.setScale(tileSize / data->assetManager.getTexture("player").getSize().x / 2, tileSize / data->assetManager.getTexture("player").getSize().y / 2);
    playerSprite.setOrigin(data->assetManager.getTexture("player").getSize().x / 2, data->assetManager.getTexture("player").getSize().y / 2);
    playerSprite.setPosition(playerPosition);
    std::cout << tileSize << std::endl;
    movementSpeed = tileSize / 36 + 1;
}

void Player::draw() {
    data->window.draw(playerSprite);
}

void Player::update(){
    if(bombHandler->checkBombCollition(playerSprite) && !playerHit){
        timePlayerHit = clock.getElapsedTime().asSeconds();
        playerHit = true;
    }else{
        if((timePlayerHit + 2.5) <= clock.getElapsedTime().asSeconds()){
            playerHit = false;
        }
    }

    if(bombCooldown){
        if((timeBombPlaced + 5) <= clock.getElapsedTime().asSeconds()){
            bombCooldown = false;
        }
    }
}

void Player::setHealth(uint8_t health){
    playerHealth = health;
}

int Player::getHealth() const {
    return playerHealth;
}

void Player::setPosition(const sf::Vector2f& pos){
    playerSprite.setPosition(pos);
}

const sf::Vector2f& Player::getPosition() const {
    return playerPosition;
}

void Player::setMovementSpeed(uint8_t speed) {
    movementSpeed = speed;   
}

int Player::getMovementSpeed() const {
    return movementSpeed;
}

sf::Sprite& Player::getSprite(){
    return playerSprite;
}

bool Player::playerMove(){
    if(arrowKeys){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            prevPosition = playerPosition;
            playerPosition.y -= movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            prevPosition = playerPosition;
            playerPosition.y += movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            prevPosition = playerPosition;
            playerPosition.x += movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            prevPosition = playerPosition;
            playerPosition.x -= movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
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
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            prevPosition = playerPosition;
            playerPosition.y += movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            prevPosition = playerPosition;
            playerPosition.x += movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            prevPosition = playerPosition;
            playerPosition.x -= movementSpeed;
            playerSprite.setPosition(playerPosition);
            return true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bombCooldown){
            bombHandler->createBomb(playerId, 3, 3, 2, playerPosition);   
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
        }
    }
    return false;
}

void Player::revertMove() {
    playerPosition = prevPosition;
    playerSprite.setPosition(playerPosition);
}

#include "../headers/player.hpp"

Player::Player(gameDataRef gameData, std::shared_ptr<BombHandler> bombHandler, ControlScheme controls, const sf::Vector2f& spawnPosition, std::string textureName, float movementSpeed, uint8_t playerHealth):
    gameData{gameData},
    bombHandler{bombHandler},
    controls{controls},
    playerPosition{spawnPosition},
    movementSpeed{movementSpeed},
    playerHealth{playerHealth},
    movementDirection{sf::Vector2i(0,0)},
    prevMovementDirection{sf::Vector2i(0,0)},
    placeBomb{true}
{
    playerSprite.setTexture(gameData->assetManager.getTexture(textureName));
    auto tileSize = gameData->tileMap.getTileMapSize().x / gameData->tileMap.getMapSize().x;
    playerSprite.setScale(tileSize / gameData->assetManager.getTexture(textureName).getSize().x / 2, tileSize / gameData->assetManager.getTexture(textureName).getSize().y / 2);
    playerSprite.setOrigin(gameData->assetManager.getTexture(textureName).getSize().x / 2, gameData->assetManager.getTexture(textureName).getSize().y / 2);
    playerSprite.setPosition(playerPosition);
}

void Player::draw() {
    gameData->window.draw(playerSprite);
}

void Player::handleInput(){
    movementDirection = controls.getDirection();
    if(controls.getBombKeyPressed() && !bombCooldown){
        bombHandler->createBomb(playerId, 4, 4, 2, playerPosition); 
        bombCooldown = true;
        timeBombPlaced = clock.getElapsedTime().asSeconds();
    }
}

void Player::update(const float & delta){
    if(bombHandler->checkBombCollision(playerSprite) && !playerHit){
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
    if(playerMove(delta) and collision.isSpriteColliding(playerSprite, gameData->tileMap.getSurroundings(playerPosition, {"empty", "biem", "spawn"}))){ //Might be possible to optimize further -- seems kind of inefficient rn
        playerSprite.setPosition(sf::Vector2f(playerPosition.x, prevPosition.y));
        if(collision.isSpriteColliding(playerSprite, gameData->tileMap.getSurroundings(playerPosition, {"empty", "biem", "spawn"}))){
            revertMove('X');
        }
        playerSprite.setPosition(sf::Vector2f(prevPosition.x, playerPosition.y));
        if(collision.isSpriteColliding(playerSprite, gameData->tileMap.getSurroundings(playerPosition, {"empty", "biem", "spawn"}))){
            revertMove('Y');
        }
    }                                                                                                                       //^^
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

void Player::setTexture(const sf::Texture & newTexture){
    playerSprite.setTexture(newTexture, true);
}

sf::Sprite& Player::getSprite(){
    return playerSprite;
}

bool Player::playerMove(const float & delta){
    if(movementDirection.x==0 && movementDirection.y==0){
        return false;
    }else{
        prevPosition = playerPosition;
        playerPosition.x += movementDirection.x * movementSpeed * delta;
        playerPosition.y += movementDirection.y * movementSpeed * delta;
        playerSprite.setPosition(playerPosition);
        prevMovementDirection = movementDirection;
        movementDirection = {0,0};
        return true;
    }
}

void Player::revertMove(const char & axis) {
    if(axis == 'X'){
        playerPosition.x = prevPosition.x;
    }else if(axis == 'Y'){
        playerPosition.y = prevPosition.y;
    }else{
        playerPosition = prevPosition;
    }
    animatedSprite.setPosition(playerPosition);
}

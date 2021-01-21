#include "../headers/player.hpp"

Player::Player(
    gameDataRef gameData, 
    std::shared_ptr<BombHandler> bombHandler, 
    ControlScheme controls, 
    const sf::Vector2f& spawnPosition, 
    std::string textureName, 
    float movementSpeed, 
    uint8_t playerHealth
):
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
    playerUpAnimationIterator = 0;
    playerUpAnimationRects.emplace_back(32, 96, 32, 32);//these dimentions are here to cut out the sprites form the spritesheet
    playerUpAnimationRects.emplace_back(64, 96, 32, 32);
    playerUpAnimationRects.emplace_back(32, 96, 32, 32);
    playerUpAnimationRects.emplace_back(0, 96, 32, 32);
    
    playerDownAnimationIterator = 0;
    playerDownAnimationRects.emplace_back(32, 0, 32, 32);//these dimentions are here to cut out the sprites form the spritesheet
    playerDownAnimationRects.emplace_back(64, 0, 32, 32);
    playerDownAnimationRects.emplace_back(32, 0, 32, 32);
    playerDownAnimationRects.emplace_back(0, 0, 32, 32);

    playerLeftAnimationIterator = 0;
    playerLeftAnimationRects.emplace_back(32, 32, 32, 32);//these dimentions are here to cut out the sprites form the spritesheet
    playerLeftAnimationRects.emplace_back(64, 32, 32, 32);
    playerLeftAnimationRects.emplace_back(32, 32, 32, 32);
    playerLeftAnimationRects.emplace_back(0, 32, 32, 32);
    
    playerRightAnimationIterator = 0;
    playerRightAnimationRects.emplace_back(32, 64, 32, 32);//these dimentions are here to cut out the sprites form the spritesheet
    playerRightAnimationRects.emplace_back(64, 64, 32, 32);
    playerRightAnimationRects.emplace_back(32, 64, 32, 32);
    playerRightAnimationRects.emplace_back(0, 64, 32, 32);

    playerSprite.setTexture(gameData->assetManager.getTexture(textureName));
    playerSprite.setTextureRect(playerDownAnimationRects.at(playerDownAnimationIterator));
    auto tileSize = gameData->tileMap.getTileMapSize().x / gameData->tileMap.getMapSize().x;
    playerSprite.setScale(
        tileSize / gameData->assetManager.getTexture(textureName).getSize().x *1.5,
        tileSize / gameData->assetManager.getTexture(textureName).getSize().y *2    
    );
    playerSprite.setOrigin(
        gameData->assetManager.getTexture(textureName).getSize().x / 6, 
        gameData->assetManager.getTexture(textureName).getSize().y / 8
    );
    playerSprite.setPosition(playerPosition);
    movementSpeed = tileSize / 36 + 1;
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
    animateMovementDirection();
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
    playerSprite.setPosition(playerPosition);
}

void Player::animateMovementDirection(){
    if(movementDirection.x == 1){
        animateMovement(playerRightAnimationRects, playerRightAnimationIterator);
    }else if(movementDirection.x == -1){
        animateMovement(playerLeftAnimationRects, playerLeftAnimationIterator);
    }else if(movementDirection.y == -1){
        animateMovement(playerUpAnimationRects, playerUpAnimationIterator);
    }else if(movementDirection.y == 1){
        animateMovement(playerDownAnimationRects, playerDownAnimationIterator);
    }
}

void Player::animateMovement(std::vector<sf::IntRect> & animationRect, unsigned int & iterator){
    if (playerAnimationClock.getElapsedTime().asSeconds() > 0.5f/animationRect.size()){
        if(iterator < animationRect.size()-1){
            iterator++;
        }else{
            iterator = 0;
        }
        playerSprite.setTextureRect(animationRect.at(iterator));
        playerAnimationClock.restart();
    }    
}
#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys, const sf::Vector2f& spawnPosition):
    data{data},
    bombHandler{bombHandler},
    arrowKeys{arrowKeys},
    playerPosition{spawnPosition}
{
    playerUpAnimationIterator = 0;
    playerUpAnimationRects.push_back(sf::IntRect(32, 96, 32, 32));
    playerUpAnimationRects.push_back(sf::IntRect(64, 96, 32, 32));
    playerUpAnimationRects.push_back(sf::IntRect(32, 96, 32, 32));
    playerUpAnimationRects.push_back(sf::IntRect(0, 96, 32, 32));
    
    playerDownAnimationIterator = 0;
    playerDownAnimationRects.push_back(sf::IntRect(32, 0, 32, 32));
    playerDownAnimationRects.push_back(sf::IntRect(64, 0, 32, 32));
    playerDownAnimationRects.push_back(sf::IntRect(32, 0, 32, 32));
    playerDownAnimationRects.push_back(sf::IntRect(0, 0, 32, 32));

    playerLeftAnimationIterator = 0;
    playerLeftAnimationRects.push_back(sf::IntRect(32, 32, 32, 32));
    playerLeftAnimationRects.push_back(sf::IntRect(64, 32, 32, 32));
    playerLeftAnimationRects.push_back(sf::IntRect(32, 32, 32, 32));
    playerLeftAnimationRects.push_back(sf::IntRect(0, 32, 32, 32));
    
    playerRightAnimationIterator = 0;
    playerRightAnimationRects.push_back(sf::IntRect(32, 64, 32, 32));
    playerRightAnimationRects.push_back(sf::IntRect(64, 64, 32, 32));
    playerRightAnimationRects.push_back(sf::IntRect(32, 64, 32, 32));
    playerRightAnimationRects.push_back(sf::IntRect(0, 64, 32, 32));

    playerSprite.setTexture(data->assetManager.getTexture("player spritesheet"));
    playerSprite.setTextureRect(playerDownAnimationRects.at(playerDownAnimationIterator));
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    playerSprite.setScale(
        tileSize / data->assetManager.getTexture("player spritesheet").getSize().x *3/2, 
        tileSize / data->assetManager.getTexture("player spritesheet").getSize().y *4/2
    );
    playerSprite.setOrigin(
        data->assetManager.getTexture("player spritesheet").getSize().x / 6, 
        data->assetManager.getTexture("player spritesheet").getSize().y / 8
    );
    playerSprite.setPosition(playerPosition);
    movementSpeed = tileSize / 36 + 1;
}

void Player::draw() {
    data->window.draw(playerSprite);
}

void Player::update(){
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
            animateMovementDirection();
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            prevPosition = playerPosition;
            playerPosition.y += movementSpeed;
            playerSprite.setPosition(playerPosition);
            animateMovementDirection();
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            prevPosition = playerPosition;
            playerPosition.x += movementSpeed;
            playerSprite.setPosition(playerPosition);
            animateMovementDirection();
            return true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            prevPosition = playerPosition;
            playerPosition.x -= movementSpeed;
            playerSprite.setPosition(playerPosition);
            animateMovementDirection();
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

void Player::animateMovementDirection(){
    sf::Vector2i movementDirection = {1, 0};
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
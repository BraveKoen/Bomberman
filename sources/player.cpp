#include "../headers/player.hpp"

Player::Player(gameDataRef data, std::shared_ptr<BombHandler> bombHandler, bool arrowKeys):
    data(data),
    bombHandler(bombHandler),
    arrowKeys(arrowKeys),
    animatedSprite()
{
    playerSprite.setTexture(data->assetManager.getTexture("Player"));
    playerSprite.setScale(0.2, 0.2);
    
    walkingAnimationDown.setSpriteSheet(data->assetManager.getTexture("Player"));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    walkingAnimationLeft.setSpriteSheet(data->assetManager.getTexture("Player"));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    walkingAnimationRight.setSpriteSheet(data->assetManager.getTexture("Player"));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    walkingAnimationUp.setSpriteSheet(data->assetManager.getTexture("Player"));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));
    
    currentAnimation = &walkingAnimationDown;
    animatedSprite.setPosition(playerPosition);
    animatedSprite.play(*currentAnimation);
}

void Player::draw() {
    data->window.draw(animatedSprite);
    animatedSprite.update(sf::seconds(100.0f));
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
            currentAnimation = &walkingAnimationUp;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            playerPosition.y += movementSpeed;
            currentAnimation = &walkingAnimationDown;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            playerPosition.x += movementSpeed;
            currentAnimation = &walkingAnimationRight;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            playerPosition.x -= movementSpeed;
            currentAnimation = &walkingAnimationLeft;
            animatedSprite.play(*currentAnimation);
        }else{
            animatedSprite.stop();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl) && !bombCooldown){
            bombHandler->createBomb(playerId, 12, 12, 5, playerPosition); 
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
        }
    }else{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            playerPosition.y -= movementSpeed;
            currentAnimation = &walkingAnimationUp;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            playerPosition.y += movementSpeed;
            currentAnimation = &walkingAnimationDown;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            playerPosition.x += movementSpeed;
            currentAnimation = &walkingAnimationRight;
            animatedSprite.play(*currentAnimation);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            playerPosition.x -= movementSpeed;
            currentAnimation = &walkingAnimationLeft;
            animatedSprite.play(*currentAnimation);
        }else{
            animatedSprite.stop();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !bombCooldown){
            bombHandler->createBomb(playerId, 12, 12, 5, playerPosition);   
            bombCooldown = true;
            timeBombPlaced = clock.getElapsedTime().asSeconds();
        }
    }
    animatedSprite.setPosition(playerPosition);
}

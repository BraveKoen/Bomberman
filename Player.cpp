#include "Player.hpp"

Player::Player(GameDataRef data):
    data(data)
    {
        playerSprite.setTexture(data->getTexture("player.png"));
    }

void Player::draw(){
    data->window.draw(playerSprite);
}

void Player::playerMove(sf::Keyboard::Key key){
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
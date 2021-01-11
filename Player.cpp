#include "Player.hpp"

Player::Player(GameDataRef data):
    data(data)
    {
        playerSprite.setTexture(data->getTexture("player.png"));
    }

void Player::draw(){
    data->window.draw(playerSprite);
}

void PLayer::playerMove(bool up, bool down, bool right, bool left){
    if(up && down){

    }
    if(right && left){

    }
    if(up){
        playerPosition.y += 1;
    }
    if(down){
        playerPosition.y -= 1;
    }
    if(right){
        playerPosition.x += 1;
    }
    if(left){
        playerPosition.x -= 1;
    }

}
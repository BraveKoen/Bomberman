#include "Player.hpp"

Player::Player(GameDataRef data):
    data(data)
    {
        playerSprite.setTexture(data->getTexture("player.png"));
    }

void Player::draw(){
    data->window.draw(playerSprite);
}
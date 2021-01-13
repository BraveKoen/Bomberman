#include "../headers/breakableWall.hpp"

breakableWall::breakableWall(gameDataRef gameData): 
    gameData(gameData)
    {}

void breakableWall::spawnWall(sf::Vector2f position){
    sf::Sprite sprite(gameData->assetManager.getTexture("breakableWall"));
    sprite.setPosition(position);
    breakableWallSprites.push_back(sprite);
}

void breakableWall::drawWall(){
    for(auto & sprite : breakableWallSprites){
        gameData->window.draw(sprite);
    }
}


const std::vector<sf::Sprite> & breakableWall::getSprites() const{
    return breakableWallSprites;
}

void breakableWall::setSprites(std::vector<sf::Sprite> & sprites){
    breakableWallSprites = sprites;
}

void breakableWall::setWallScale(sf::Vector2f scale){
    for(auto & sprite : breakableWallSprites){
        sprite.setScale(scale);
    }
}

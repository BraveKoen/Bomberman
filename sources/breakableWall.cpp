#include "../headers/breakableWall.hpp"

BreakableWall::BreakableWall(gameDataRef gameData): 
    gameData(gameData)
    {}

void BreakableWall::spawnWall(sf::Vector2f position){
    sf::Sprite sprite(gameData->assetManager.getTexture("breakableWall"));
    sprite.setPosition(position);
    breakableWallSprites.push_back(sprite);
}

void BreakableWall::drawWall(){
    for(auto & sprite : breakableWallSprites){
        gameData->window.draw(sprite);
    }
}

const std::vector<sf::Sprite> & BreakableWall::getSprites() const{
    return breakableWallSprites;
}

void BreakableWall::setSprites(std::vector<sf::Sprite> & sprites){
    breakableWallSprites = sprites;
}

void BreakableWall::setWallScale(sf::Vector2f scale){
    for(auto & sprite : breakableWallSprites){
        sprite.setScale(scale);
    }
}

#include "../headers/unbreakableWall.hpp"

unbreakableWall::unbreakableWall(gameDataRef gameData): 
    gameData(gameData)
    {}

void unbreakableWall::spawnWall(sf::Vector2f position){
    sf::Sprite sprite(gameData->assetManager.getTexture("unbreakableWall"));
    sprite.setPosition(position);
    unbreakableWallSprites.push_back(sprite);
}

void unbreakableWall::drawWall(){
    for(auto & sprite : unbreakableWallSprites){
        gameData->window.draw(sprite);
    }
}


const std::vector<sf::Sprite> & unbreakableWall::getSprites() const{
    return unbreakableWallSprites;
}

void unbreakableWall::setSprites(std::vector<sf::Sprite> & sprites){
    unbreakableWallSprites = sprites;
}

void unbreakableWall::setWallScale(sf::Vector2f scale){
    for(auto & sprite : unbreakableWallSprites){
        sprite.setScale(scale);
    }
}

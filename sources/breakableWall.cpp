breakableWall::breakableWall(gameDataRef gameData): 
    gameData(gameData)
    {}

void breakableWall::spawnWall(sf::Vector2f position);
    sf::Sprite sprite(this->_data->assets.GetTexture("breakableWall"));
    sprite.setPosition(position);
    pipeSprites.push_back(sprite);

void breakableWall::drawWall(){
    for(auto & sprite : breakableWallSprites){
        gameData.window.draw(sprite);
    }
}


const breakableWall::std::vector<sf::Sprite> &getSprites() const{
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

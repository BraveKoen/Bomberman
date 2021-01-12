unbreakableWall::unbreakableWall(GameData gameData): 
    gameData(gameData)
    {}

void unbreakableWall::spawnWall(sf::Vector2f position);
    sf::Sprite sprite(this->_data->assets.GetTexture("unbreakableWall"));
    sprite.setPosition(position);
    pipeSprites.push_back(sprite);

void unbreakableWall::drawWall(){
    for(auto & sprite : unbreakableWallSprites){
        gameData.window.draw(sprite);
    }
}


const unbreakableWall::std::vector<sf::Sprite> &getSprites() const{
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

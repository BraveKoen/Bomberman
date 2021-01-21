#include "../headers/bomb.hpp"

Bomb::Bomb(gameDataRef data, int playerId, int lenghtX, int lenghtY, float explodeTime, float timeCreated, sf::Vector2f pos):
    data(data),
    id(playerId),
    lengthX(lenghtX),
    lengthY(lenghtY),
    explodeTime(explodeTime),
    timeCreated(timeCreated),
    bombPosition(pos)
{
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    bombSprite.setTexture(data->assetManager.getTexture("dynamite"));
    bombSprite.setScale(tileSize / data->assetManager.getTexture("dynamite").getSize().x, tileSize / data->assetManager.getTexture("dynamite").getSize().y);
    bombSprite.setOrigin(data->assetManager.getTexture("dynamite").getSize().x / 2, data->assetManager.getTexture("dynamite").getSize().y / 2);
    setPos(pos);
}

void Bomb::draw(){
    if(!isDone){
        data->window.draw(bombSprite);
    }
}

void Bomb::setPos(sf::Vector2f pos){
    auto posVec = data->tileMap.screenPosToTilePos(pos);
    auto center = data->tileMap.tilePosToScreenPos(posVec);
    bombSprite.setPosition(center);
}

void Bomb::explode() {
    auto posVec = data->tileMap.screenPosToTilePos(bombPosition);
    auto tileMapLength = data->tileMap.getMapSize();
    bool destroyedX = false;
    bool destroyedY = false; 
    bool destroyedXL = false;
    bool destroyedYL = false;
    destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y});
    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y}, "biem");
    for(int i = 1; i < (lengthX); i++){ // X as
        if(!destroyedX && (posVec.x + i) >! tileMapLength.x){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x + i, posVec.y}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x + i, posVec.y});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x + i, posVec.y}).getType() == "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x + i, posVec.y}, "biem");
                    destroyedX = true;
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x + i, posVec.y}, "biem");
                }     
            }else{
                destroyedX = true;
            }
        }
        if(!destroyedXL && (posVec.x != 0)){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x - i, posVec.y}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x - i, posVec.y});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x - i, posVec.y}).getType() == "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x - i, posVec.y}, "biem");
                    destroyedXL = true;
                    
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x - i, posVec.y}, "biem");
                }     
            }else{
                destroyedXL = true;
            }
        }
    }
    for(int j = 1; j < (lengthY); j++){ // Y as
        if(!destroyedY && ((posVec.y + j) >! tileMapLength.y)){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + j}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y + j});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + j}).getType() == "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y + j}, "biem");
                    destroyedY = true;       
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y + j}, "biem");
                }     
            }else{
                destroyedY = true;
            }
        }

        if(!destroyedYL && (posVec.y != 0)){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - j}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y - j});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - j}).getType() == "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y - j}, "biem");
                    destroyedYL = true;
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y - j}, "biem");
                }     
            }else{
                destroyedYL = true;
            }
        }
    }
}

bool Bomb::isExploded(float currentTime){
    if((timeCreated + explodeTime < currentTime) && !isDone){
        explode();
        isDone = true;
        return false;
    }
    if((timeCreated + explodeTime + 2 < currentTime) && isDone){
        clearBomb();
        return true;
    }
    return false;
}

void Bomb::clearBomb(){
    for(auto &pos : destroyedTiles){
        data->tileMap.setTile(pos, "empty");
    }
}

int Bomb::getBombId(){
    return id;
}

bool Bomb::playerHit(){
    return false;
}

bool Bomb::bombColliding(const sf::Sprite& target){
    for(auto &pos : destroyedTiles){
        auto test = data->tileMap.getTile(pos);
        if(target.getGlobalBounds().intersects(test.getBounds())){
            return true;
        }
    }
    return false;
}

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
    bombSprite.setTexture(data->assetManager.getTexture("Dynamite"));
    bombSprite.setScale(tileSize / data->assetManager.getTexture("Dynamite").getSize().x, tileSize / data->assetManager.getTexture("Dynamite").getSize().y);
    bombSprite.setOrigin(data->assetManager.getTexture("Dynamite").getSize().x / 2, data->assetManager.getTexture("Dynamite").getSize().y / 2);
    setPos(pos);
}

void Bomb::draw(){
    data->window.draw(bombSprite);
}

void Bomb::setPos(sf::Vector2f pos){
    auto posVec = data->tileMap.screenPosToTilePos(pos);
    auto center = data->tileMap.tilePosToScreenPos(posVec);
    bombSprite.setPosition(center);
}

void Bomb::explode() {
    auto posVec = data->tileMap.screenPosToTilePos(bombPosition);
    auto tileMapLenght = data->tileMap.getMapSize();
    bool destroyedX = false;
    bool destroyedY = false; 
    bool destroyedXL = false;
    bool destroyedYL = false;
    destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y});
    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y}, "biem");
    for(int i = 1; i < (lengthX); i++){ // X as
        if((posVec.x + i) >= tileMapLenght.x){
            continue;
        }else if(!destroyedX){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x + i, posVec.y})!= "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x + i, posVec.y});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x + i, posVec.y})== "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x + i, posVec.y}, "biem");
                    destroyedX = true;
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x + i, posVec.y}, "biem");
                }     
            }else{
                destroyedX = true;
            }
        }
        if(posVec.x == 0){
            continue;
        }else if(!destroyedXL){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x - i, posVec.y})!= "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x - i, posVec.y});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x - i, posVec.y})== "break"){
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
    for(int i = 1; i < (lengthY); i++){ // Y as
        if((posVec.y + i) >= tileMapLenght.y){
            continue;
        }else if(!destroyedY){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + i})!= "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y + i});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + i})== "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y + i}, "biem");
                    destroyedY = true;       
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y + i}, "biem");
                }     
            }else{
                destroyedY = true;
            }
        }
        if(posVec.y == 0){
            continue;
        }else if(!destroyedYL){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - i})!= "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y - i});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - i})== "break"){
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y - i}, "biem");
                    destroyedYL = true;
                }else{
                    data->tileMap.setTile(sf::Vector2u{posVec.x, posVec.y - i}, "biem");
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
    for(auto &tile : destroyedTiles){
        data->tileMap.setTile(tile, "empty");
    }
}

int Bomb::getBombId(){
    return id;
}

bool Bomb::playerHit(){
    return false;
}

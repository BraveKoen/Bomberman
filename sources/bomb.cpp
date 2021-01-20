#include "../headers/bomb.hpp"

Bomb::Bomb(
    gameDataRef data, 
    int playerId, 
    int lenghtX, 
    int lenghtY, 
    float explodeTime, 
    float timeCreated, 
    sf::Vector2f pos
):
    data(data),
    id(playerId),
    lengthX(lenghtX),
    lengthY(lenghtY),
    explodeTime(explodeTime),
    timeCreated(timeCreated),
    bombPosition(pos)
{
    auto tileSize = data->tileMap.getTileMapSize().x / data->tileMap.getMapSize().x;
    
    bombFuseAnimationIterator = 0;
    bombFuseAnimation.push_back(data->assetManager.getTexture("bomb fuse frame 1"));
    bombFuseAnimation.push_back(data->assetManager.getTexture("bomb fuse frame 2"));
    bombFuseAnimation.push_back(data->assetManager.getTexture("bomb fuse frame 3"));
    bombFuseAnimation.push_back(data->assetManager.getTexture("bomb fuse frame 4"));
    
    bombExplosionAnimationIterator = 0;
    bombExplosionAnimation.push_back(data->assetManager.getTexture("bomb explosion frame 1"));
    bombExplosionAnimation.push_back(data->assetManager.getTexture("bomb explosion frame 2"));
    bombExplosionAnimation.push_back(data->assetManager.getTexture("bomb explosion frame 3"));
    bombExplosionAnimation.push_back(data->assetManager.getTexture("bomb explosion frame 4"));

    bombSprite.setTexture(bombFuseAnimation.at(bombFuseAnimationIterator));
    bombSprite.setScale(
        tileSize / data->assetManager.getTexture("bomb fuse frame 1").getSize().x, 
        tileSize / data->assetManager.getTexture("bomb fuse frame 1").getSize().y
    );
    bombSprite.setOrigin(
        data->assetManager.getTexture("bomb fuse frame 1").getSize().x / 2, 
        data->assetManager.getTexture("bomb fuse frame 1").getSize().y / 2
    );
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
        if(posVec.x == 0){
            continue;
        }else if(!destroyedXL){
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
    for(int i = 1; i < (lengthY); i++){ // Y as
        if((posVec.y + i) >= tileMapLenght.y){
            continue;
        }else if(!destroyedY){
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + i}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y + i});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y + i}).getType() == "break"){
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
            if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - i}).getType() != "solid"){
                destroyedTiles.push_back(sf::Vector2u{posVec.x, posVec.y - i});
                if(data->tileMap.getTile(sf::Vector2u{posVec.x, posVec.y - i}).getType() == "break"){
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
    if((timeCreated + explodeTime < currentTime) && !primed){
        explode();
        primed = true;
        return false;
    }
    if((timeCreated + explodeTime + 2 < currentTime) && primed){
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

void Bomb::animateFuse(){
    if (clock.getElapsedTime().asSeconds() > 0.5f/bombFuseAnimation.size()){
        if(bombFuseAnimationIterator < bombFuseAnimation.size()-1){
            bombFuseAnimationIterator++;
        }else{
            bombFuseAnimationIterator = 0;
        }
        bombSprite.setTexture(bombFuseAnimation.at(bombFuseAnimationIterator));
        clock.restart();
    }
}

void Bomb::animateExplosion(){
    if (clock.getElapsedTime().asSeconds() > 0.5f/bombExplosionAnimation.size()){
        if(bombExplosionAnimationIterator < bombExplosionAnimation.size()-1){
            bombExplosionAnimationIterator++;
        }else{
            bombExplosionAnimationIterator = 0;
        }
        bombSprite.setTexture(bombExplosionAnimation.at(bombExplosionAnimationIterator));
        clock.restart();
    }
}

bool Bomb::getPrimed(){
    return primed;
}
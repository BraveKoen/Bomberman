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
    bombFuseAnimationRects.push_back(sf::IntRect(0, 0, 450, 375));
    bombFuseAnimationRects.push_back(sf::IntRect(450, 0, 450, 375));
    bombFuseAnimationRects.push_back(sf::IntRect(0, 375, 450, 375));
    bombFuseAnimationRects.push_back(sf::IntRect(450, 375, 450, 375));

    bombExplosionAnimationIterator = 0;
    bombExplosionAnimationRects.push_back(sf::IntRect(0, 750, 450, 375));
    bombExplosionAnimationRects.push_back(sf::IntRect(450, 750, 450, 375));
    bombExplosionAnimationRects.push_back(sf::IntRect(0, 1125, 450, 375));
    bombExplosionAnimationRects.push_back(sf::IntRect(450, 1125, 450, 375));

    bombSprite.setTexture(data->assetManager.getTexture("bomb spritesheet"));
    bombSprite.setTextureRect(bombFuseAnimationRects.at(bombFuseAnimationIterator));
    bombSprite.setScale(
        tileSize / data->assetManager.getTexture("bomb spritesheet").getSize().x*2, 
        tileSize / data->assetManager.getTexture("bomb spritesheet").getSize().y*4
    );
    bombSprite.setOrigin(
        data->assetManager.getTexture("bomb spritesheet").getSize().x / 4, 
        data->assetManager.getTexture("bomb spritesheet").getSize().y / 8
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

bool Bomb::bombColliding(const sf::Sprite& target){
    for(auto &pos : destroyedTiles){
        auto test = data->tileMap.getTile(pos);
        if(target.getGlobalBounds().intersects(test.getBounds())){
            return true;
        }
    }
    return false;
}
    
void Bomb::animateFuse(){
    if (clock.getElapsedTime().asSeconds() > 0.5f/bombFuseAnimationRects.size()){
        if(bombFuseAnimationIterator < bombFuseAnimationRects.size()-1){
            bombFuseAnimationIterator++;
        }else{
            bombFuseAnimationIterator = 0;
        }
        bombSprite.setTextureRect(bombFuseAnimationRects.at(bombFuseAnimationIterator));
        clock.restart();
    }
}

void Bomb::animateExplosion(){
    if (clock.getElapsedTime().asSeconds() > 0.5f/bombExplosionAnimationRects.size()){
        if(bombExplosionAnimationIterator < bombExplosionAnimationRects.size()-1){
            bombExplosionAnimationIterator++;
        }else{
            bombExplosionAnimationIterator = 0;
        }
        bombSprite.setTextureRect(bombExplosionAnimationRects.at(bombExplosionAnimationIterator));
        clock.restart();
    }
}

bool Bomb::getPrimed(){
    return primed;
}

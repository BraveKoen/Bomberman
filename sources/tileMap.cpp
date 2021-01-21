#include "../headers/tileMap.hpp"
#include "../headers/game.hpp"
#include "../headers/tile.hpp"

void TileMap::expandTileMap(){
    for(unsigned int i=0; i<mapSize.x; i++){
        if(i>=map.size()){
            map.push_back(std::vector<Tile>());
        }
        for(unsigned int j=map[i].size(); j<mapSize.y; j++){
            map[i].push_back(Tile());
        }
    }
}

void TileMap::processSizeAndPositionChanges(){
    background.setPosition(position);
    background.setScale(size.x/background.getTexture()->getSize().x, size.y/background.getTexture()->getSize().y);
    for(unsigned int i=0; i<map.size(); i++){
        for(unsigned int j=0; j<map[i].size(); j++){
            if(map[i][j].getType() != "empty"){
                map[i][j].setPosition(sf::Vector2f(position.x+((size.x/mapSize.x)*i), position.y+((size.y/mapSize.y)*j)));
                map[i][j].setScale(sf::Vector2f((size.x/mapSize.x)/map[i][j].getTexture()->getSize().x, (size.y/mapSize.y)/map[i][j].getTexture()->getSize().y));
            }
        }
    }
}

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, gameDataRef gameData, sf::Vector2u mapSize):
    position(position),
    size(size),
    gameData(gameData),
    mapSize(mapSize)
{
    expandTileMap();
    background.setTexture(gameData->assetManager.getTexture("background"));
    processSizeAndPositionChanges();
}

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, gameDataRef gameData, std::vector<std::vector<std::string>> newMap, sf::Vector2u mapSize):
    position(position),
    size(size),
    gameData(gameData),
    mapSize(mapSize)
{
    expandTileMap();
    setMap(newMap);
    background.setTexture(gameData->assetManager.getTexture("background"));
    processSizeAndPositionChanges();
}

sf::Vector2u TileMap::screenPosToTilePos(sf::Vector2f screenPosition){  //Returns the tile that the given screenspace position is in
    return sf::Vector2u((screenPosition.x-position.x)/(size.x/mapSize.x), (screenPosition.y-position.y)/(size.y/mapSize.y));
}

sf::Vector2f TileMap::tilePosToScreenPos(sf::Vector2u tilePosition){ //Returns the center of the tile in screenspace
    return sf::Vector2f((size.x/mapSize.x*(tilePosition.x+1))+position.x-(size.x/mapSize.x/2), (size.y/mapSize.y*(tilePosition.y+1))+position.y-(size.y/mapSize.y/2));
}

void TileMap::setTileMapPosition(sf::Vector2f newPosition){
    position = newPosition;
    processSizeAndPositionChanges();
}

void TileMap::setTileMapSize(sf::Vector2f newSize){
    size = newSize;
    processSizeAndPositionChanges();
}

void TileMap::setMapSize(sf::Vector2u newMapSize){
    mapSize = newMapSize;
    processSizeAndPositionChanges();
}

void TileMap::setMap(std::vector<std::vector<std::string>> newMap){ //If newMap is not the same size as the tilemap only a portion (of whichever is larger) will be changed/applied properly
    unsigned int xSize;
    if(newMap.size() > mapSize.x){
        xSize = mapSize.x;
    }else{
        xSize = newMap.size();
    }
    for(unsigned int i=0; i < xSize; i++){
        unsigned int ySize;
        if(newMap[i].size() > mapSize.y){
            ySize = mapSize.y;
        }else{
            ySize = newMap[i].size();
        }
        for(unsigned int j=0; j < ySize; j++){
            if(newMap[i][j] != "empty" ){
                map[i][j].setTexture(gameData->assetManager.getTexture(newMap[i][j]));
            }
            map[i][j].setType(newMap[i][j]);
        }
    }
}

sf::Vector2f TileMap::getTileMapPosition()const{
    return position;
}

sf::Vector2f TileMap::getTileMapSize()const{
    return size;
}

sf::Vector2u TileMap::getMapSize()const{
    return mapSize;
}

std::vector<std::vector<Tile>> TileMap::getMap()const{
    return map;
}

void TileMap::setTile(sf::Vector2u tilePosition, std::string type){
    map[tilePosition.x][tilePosition.y].setType(type);
    if(type != "empty"){
        map[tilePosition.x][tilePosition.y].setTexture(gameData->assetManager.getTexture(type));
    }   
    map[tilePosition.x][tilePosition.y].setScale(sf::Vector2f((size.x/mapSize.x)/map[tilePosition.x][tilePosition.y].getTexture()->getSize().x, (size.y/mapSize.y)/map[tilePosition.x][tilePosition.y].getTexture()->getSize().y));
}

void TileMap::setTile(sf::Vector2f screenPosition, std::string type){
    setTile(screenPosToTilePos(screenPosition), type);
}

Tile TileMap::getTile(sf::Vector2u tilePosition)const{
    return map.at(tilePosition.x).at(tilePosition.y);
}

Tile TileMap::getTile(sf::Vector2f screenPosition){
    return getTile(screenPosToTilePos(screenPosition));
}

std::vector<sf::Vector2u> TileMap::searchForType(const std::string & type){
    std::vector<sf::Vector2u> positions;
    for(unsigned int i=0; i<map.size(); i++){
        for(unsigned int j=0; j<map[i].size(); j++){
            if(map[i][j].getType() == type){
                positions.push_back(sf::Vector2u(i,j));
            }
        }
    }
    return positions;
}

std::vector<Tile> TileMap::getSurroundings(const sf::Vector2u & tilePosition, const std::vector<std::string> & exclusions, const unsigned int & range){
    std::vector<Tile> surroundings;
    const auto xStart = tilePosition.x < range ? 0 : tilePosition.x-range;
    const auto yStart = tilePosition.y < range ? 0 : tilePosition.y-range;
    auto xEnd = tilePosition.x+range; if(xEnd > mapSize.x) xEnd=mapSize.x;
    auto yEnd = tilePosition.y+range; if(yEnd > mapSize.y) yEnd=mapSize.y;
    bool pushBack = true;
    for(auto i=xStart; i<=xEnd; i++){
        for(auto j=yStart; j<=yEnd; j++){
            for(std::string type : exclusions){
                if(map[i][j].getType() == type){
                    pushBack = false;
                    break;
                }
            }
            if(pushBack){
                surroundings.push_back(map[i][j]);
            }else{
                pushBack = true;
            }
        }
    }
    return surroundings;
}

std::vector<Tile> TileMap::getSurroundings(const sf::Vector2f & screenPosition, const std::vector<std::string> & exclusions, const unsigned int & range){
    return getSurroundings(screenPosToTilePos(screenPosition), exclusions, range);
}

void TileMap::draw(bool drawPlayerSpawns){
    gameData->window.draw(background);
    for(unsigned int i=0; i<map.size(); i++){
        for(unsigned int j=0; j<map[i].size(); j++){
            if(map[i][j].getType() != "empty"){
                if(map[i][j].getType() != "spawn" || drawPlayerSpawns){
                    map[i][j].setPosition(sf::Vector2f(position.x+((size.x/mapSize.x)*i), position.y+((size.y/mapSize.y)*j)));
                    map[i][j].setScale(sf::Vector2f((size.x/mapSize.x)/map[i][j].getTexture()->getSize().x, (size.y/mapSize.y)/map[i][j].getTexture()->getSize().y));
                    map[i][j].draw(gameData->window);
                }
            }
        }
    }
}

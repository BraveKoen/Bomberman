#include "../headers/tileMap.hpp"
#include "../headers/game.hpp"

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, sf::Vector2u mapSize):
    position(position),
    size(size),
    mapSize(mapSize)
    {}

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, std::vector<std::vector<std::string>> map, sf::Vector2u mapSize):
    position(position),
    size(size),
    map(map),
    mapSize(mapSize)
    {}

sf::Vector2u TileMap::screenPosToTilePos(sf::Vector2f screenPosition){  //Returns the tile that the given screenspace position is in
    return sf::Vector2u((screenPosition.x-position.x)/(size.x/mapSize.x), (screenPosition.y-position.y)/(size.y/mapSize.y));
}

sf::Vector2f TileMap::tilePosToScreenPos(sf::Vector2u tilePosition){ //Returns the center of the tile in screenspace
    return sf::Vector2f((size.x/mapSize.x*tilePosition.x)+position.x-(size.x/mapSize.x/2), (size.y/mapSize.y*tilePosition.y)+position.y-(size.y/mapSize.y/2));
}

void TileMap::setTileMapPosition(sf::Vector2f newPosition){
    position = newPosition;
}

void TileMap::setTileMapSize(sf::Vector2f newSize){
    size = newSize;
}

void TileMap::setMapSize(sf::Vector2u newMapSize){
    mapSize = newMapSize;
}

void TileMap::setMap(std::vector<std::vector<std::string>> newMap){
    map = newMap;
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

std::vector<std::vector<std::string>> TileMap::getMap()const{
    return map;
}

void TileMap::setTile(sf::Vector2u tilePosition, std::string type){
    map[tilePosition.x][tilePosition.y] = type;
}

void TileMap::setTile(sf::Vector2f screenPosition, std::string type){
    setTile(screenPosToTilePos(screenPosition), type);
}

std::string TileMap::getTile(sf::Vector2u tilePosition)const{
    return map.at(tilePosition.x).at(tilePosition.y);
}

std::string TileMap::getTile(sf::Vector2f screenPosition){
    return getTile(screenPosToTilePos(screenPosition));
}
#include "../headers/tileMap.hpp"

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, sf::Vector2u mapSize):
    position(position),
    size(size),
    mapSize(mapSize)
    {}

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
    return position
}

sf::Vector2f TileMap::getTileMapSize()const{

}

sf::Vector2u TileMap::getMapSize()const{

}

std::vector<std::vector<std::string>> TileMap::setMap()const{

}

void TileMap::setTile(sf::Vector2u tilePosition, std::string type){

}

void TileMap::setTile(sf::Vector2f screenPosition, std::string type){

}

std::string TileMap::getTile(sf::Vector2u tilePosition)const{

}

std::string TileMap::getTile(sf::Vector2f screenPosition)const{

}

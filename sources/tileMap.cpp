#include "../headers/tileMap.hpp"

TileMap::TileMap(sf::Vector2f position, sf::Vector2f size, sf::Vector2u mapSize=sf::Vector2u(15,15)):
    position(position),
    size(size),
    mapSize(mapSize)
    {}

void TileMap::setPosition(sf::Vector2f newPosition){
    position = newPosition;
}

void TileMap::setSize(sf::Vector2f newSize){
    size = newSize;
}

void TileMap::setMapSize(sf::Vector2u newMapSize){
    mapSize = newMapSize;
}
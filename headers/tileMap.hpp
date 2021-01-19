#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "tile.hpp"
#include "definitions.hpp"
#include "tile.hpp"

class TileMap{
private:
    sf::Vector2f position;
    sf::Vector2f size;
    gameDataRef gameData;
    std::vector<std::vector<Tile>> map;
    sf::Vector2u mapSize;
    sf::Sprite background;
    void expandTileMap();
    void processSizeAndPositionChanges();
public:
    TileMap() = default;
    TileMap(sf::Vector2f position, sf::Vector2f size, gameDataRef gameData, sf::Vector2u mapSize=sf::Vector2u(15,15));
    TileMap(sf::Vector2f position, sf::Vector2f size, gameDataRef gameData, std::vector<std::vector<std::string>> newMap, sf::Vector2u mapSize=sf::Vector2u(15,15));
    //Screen coords vs tile coords math functions
    sf::Vector2u screenPosToTilePos(sf::Vector2f screenPosition); //Returns the tile that the given screenspace position is in
    sf::Vector2f tilePosToScreenPos(sf::Vector2u tilePosition); //Returns the center of the tile in screenspace
    //General setters
    void setTileMapPosition(sf::Vector2f newPosition);
    void setTileMapSize(sf::Vector2f newSize);
    void setMapSize(sf::Vector2u newMapSize);
    void setMap(std::vector<std::vector<std::string>> newMap); //If newMap is not the same size as the tilemap only a portion (of whichever is larger) will be changed/applied properly
    //Generals getters
    sf::Vector2f getTileMapPosition()const;
    sf::Vector2f getTileMapSize()const;
    sf::Vector2u getMapSize()const;
    std::vector<std::vector<Tile>> getMap()const;
    //Tile setters and getters
    void setTile(sf::Vector2u tilePosition, std::string type); //Based on tile coordinates
    void setTile(sf::Vector2f screenPosition, std::string type); //Based on screen coordinates
    Tile getTile(sf::Vector2u tilePosition)const; //Based on tile coordinates
    Tile getTile(sf::Vector2f screenPosition); //Based on screen coordinates

    std::vector<sf::Vector2u> searchForType(const std::string & type);

    std::vector<Tile> getSurroundings(const sf::Vector2u & tilePosition, const unsigned int & range, const bool & includeEmpty);
    std::vector<Tile> getSurroundings(const sf::Vector2f & screenPosition, const unsigned int & range=1, const bool & includeEmpty=false); //range is the number of tiles away from the position we return (including corners). 
                                                                                                                                  //includeEmpty means to include tiles with type "empty" and textureless sprites (dont draw these!)
    void draw(bool drawPlayerSpawns=false);
};

#endif // __TILEMAP_HPP__

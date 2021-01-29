#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "tile.hpp"

class TileMap{
private:
    gameDataRef gameData;
    sf::Vector2f position;
    sf::Vector2f size;
    std::vector<std::vector<std::string>> layoutMap;
    std::vector<std::vector<Tile>> map;
    sf::Vector2u mapSize;
    sf::Sprite background;
    void expandTileMap();
    void processSizeAndPositionChanges();
public:
    TileMap() = default;
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        std::vector<std::vector<std::string>> newMap
    );
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        std::vector<std::vector<std::string>> newMap,
        const sf::Vector2u & mapSize
    );
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        const sf::Vector2u & mapSize
    );
    // Screen coords vs tile coords math functions
    // Returns the tile that the given screenspace position is in
    sf::Vector2u screenPosToTilePos(const sf::Vector2f & screenPosition)const;
    // Returns the center of the tile in screenspace
    sf::Vector2f tilePosToScreenPos(const sf::Vector2u & tilePosition)const;
    std::vector<sf::Vector2u> searchForType(const std::string & type)const;

    // General setters
    void setTileMapPosition(const sf::Vector2f & newPosition);
    void setTileMapSize(const sf::Vector2f & newSize);
    void setMapSize(const sf::Vector2u & newMapSize);

    // If layoutMap is not the same size as the tilemap only a portion
    // (of whichever is larger) will be changed/applied properly
    void loadMap();

    // Generals getters
    const sf::Vector2f & getTileMapPosition()const;
    const sf::Vector2f & getTileMapSize()const;
    const sf::Vector2u & getMapSize()const;
    const std::vector<std::vector<Tile>> & getMap()const;

    // Tile setters and getters
    // Based on tile coordinates
    void setTile(const sf::Vector2u & tilePosition, std::string type);
    // Based on screen coordinates
    void setTile(const sf::Vector2f & screenPosition, std::string type);
    // Based on tile coordinates
    const Tile & getTile(const sf::Vector2u & tilePosition)const;
    // Based on screen coordinates
    const Tile & getTile(const sf::Vector2f & screenPosition)const;

    // range is the number of tiles away from the position we return (including corners).
    // exclusions are the types to exclude from return
    std::vector<Tile> getSurroundings(
        const sf::Vector2u & tilePosition,
        const std::vector<std::string> & exclusions,
        unsigned int range = 1
    );
    std::vector<Tile> getSurroundings(
        const sf::Vector2f & screenPosition,
        const std::vector<std::string> & exclusions,
        unsigned int range = 1
    );
    void draw(bool drawPlayerSpawns=false);

    std::vector<std::vector<std::string>> getLayoutMap()const;
};

#endif // __TILEMAP_HPP__

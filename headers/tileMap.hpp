#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "tile.hpp"

/// \brief
/// TileMap class
/// \details
/// The TileMap class is essentially a datatype for storing a two-dimensional vector of Tile(s). Including various getters and setters, as well as it's own coordinate space with conversion functions.
/// Due to the coordinate space and the way the draw function works (and the fact that the tilemap has it's own background) the TileMap can almost be treated like a window inside of a window, if you catch my drift.
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
    /// \brief
    /// Default constructor
    /// \details
    /// Default constructor with no parameters. This one shouldn't really be used normally, it's only used by the gameData to construct a default empty TileMap, but this one should always be replaced before usage.
    TileMap() = default;
    /// \brief
    /// Contructor with map
    /// \details
    /// This constrcuctor will autmatically determine the size of the given map.
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        std::vector<std::vector<std::string>> newMap
    );
    /// \brief
    /// Constrcutor with map and mapSize
    /// \details
    /// This constructor allows you to manually provide the mapSize.
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        std::vector<std::vector<std::string>> newMap,
        const sf::Vector2u & mapSize
    );
    /// \brief
    /// Constructor with mapSize
    /// \details
    /// This constructor allows you to determine the mapSize without setting the map yet.
    TileMap(
        gameDataRef gameData,
        const sf::Vector2f & position,
        const sf::Vector2f & size,
        const sf::Vector2u & mapSize
    );
    /// \brief
    /// Screenspace to tilespace conversion
    /// \details
    /// This function converts screenspace coordinates to tilespace coordinates. It basically returns the tile in which the given point is located.
    sf::Vector2u screenPosToTilePos(const sf::Vector2f & screenPosition)const;
    /// \brief
    /// Tilespace to screenspace conversion
    /// \details
    /// This function converts tilespace coordinates to screenspace coordinates. Returns the center of the tile at tilePosition.
    sf::Vector2f tilePosToScreenPos(const sf::Vector2u & tilePosition)const;

    /// \brief
    /// Search tilemap for tiles of type
    /// \details
    /// Returns a vector with the tilespace positions of tiles with the given type.
    std::vector<sf::Vector2u> searchForType(const std::string & type)const;

    // General setters
    /// \brief
    /// Setter for tileMapPosition
    /// \details
    /// Allows you to set the screenspace position of the entire tilemap.
    void setTileMapPosition(const sf::Vector2f & newPosition);

    /// \brief
    /// Setter for tilemap size
    /// \details
    /// Allows you to set the screenspace size of the entire tilemap.
    void setTileMapSize(const sf::Vector2f & newSize);

    /// \brief
    /// Setter for map size
    /// \details
    /// Allows you to set the tilespace dimensions of the tilemap (for example 10 tiles by 10 tiles).
    void setMapSize(const sf::Vector2u & newMapSize);

    
    /// \brief
    /// Loads the layoutmap into the map
    /// \details
    /// This function loads the layoutmap (a 2D vector of string type) into the actual map of tiles.
    /// If layoutMap is not the same size as the tilemap only a portion (of whichever is larger) will be changed/applied properly.
    void loadMap();

    // Generals getters
    /// \brief
    /// Getter for tilemap position
    /// \details
    /// Returns the screenspace position of the entire tilemap.
    const sf::Vector2f & getTileMapPosition()const;

    /// \brief
    /// Getter for tilemap size
    /// \details
    /// Returns the screenspace size of the entire tilemap.
    const sf::Vector2f & getTileMapSize()const;

    /// \brief
    /// Getter for map size
    /// \details
    /// Returns the tilespace dimension of the map (for example 10 tiles by 10 tiles).
    const sf::Vector2u & getMapSize()const;

    /// \brief
    /// Getter for the map
    /// \details
    /// Returns the entire map as a 2D vector of Tile(s).
    const std::vector<std::vector<Tile>> & getMap()const;

    // Tile setters and getters
    /// \brief
    /// Setter for tile type
    /// \details
    /// Sets the tile type at the tilespace tilePosition to type
    void setTile(const sf::Vector2u & tilePosition, std::string type);
    
    /// \brief
    /// Setter for tile type
    /// \details
    /// Sets the tile type at the screenscpae screenPosition to type
    void setTile(const sf::Vector2f & screenPosition, std::string type);
    
    /// \brief
    /// Getter for tile
    /// \details
    /// Returns the tile at tilespace tilePosition
    const Tile & getTile(const sf::Vector2u & tilePosition)const;
    
    /// \brief
    /// Getter for tile
    /// \details
    /// Returns the tile at screenspace screenPosition
    const Tile & getTile(const sf::Vector2f & screenPosition)const;

    /// \brief
    /// Getter for surroundings
    /// \details
    /// Return a vector of tiles around the given tilespace position.
    /// Excludes the tiles of all types in vector<string> exclusions.
    /// Up to a radius of range. Default 1 (direct surroundings).
    std::vector<Tile> getSurroundings(
        const sf::Vector2u & tilePosition,
        const std::vector<std::string> & exclusions,
        unsigned int range = 1
    );

    /// \brief
    /// Getter for surroundings
    /// \details
    /// Return a vector of tiles around the given screenspace position.
    /// Excludes the tiles of all types in vector<string> exclusions.
    /// Up to a radius of range. Default 1 (direct surroundings).
    std::vector<Tile> getSurroundings(
        const sf::Vector2f & screenPosition,
        const std::vector<std::string> & exclusions,
        unsigned int range = 1
    );

    /// \brief
    /// Draws the tilemap
    /// \details
    /// This function draws the tilemap background and all tiles.
    void draw(bool drawPlayerSpawns=false);

    std::vector<std::vector<std::string>> getLayoutMap()const;
};

#endif // __TILEMAP_HPP__

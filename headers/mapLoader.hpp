#ifndef __MAPLOADER_HPP__
#define __MAPLOADER_HPP__

#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "tileMap.hpp"
#include "tile.hpp"

// defined but not used?
// using mapData = struct {std::string name; TileMap tileMap;};
typedef struct {std::string name; TileMap tileMap;} mapData;

class MapLoader {
private:
    std::string resourceLocation;
    std::string fileExtension;
    uint_fast8_t maxTileMaps;
public:
    MapLoader();
    MapLoader(std::string resourceLocation);
    MapLoader(std::string resourceLocation, std::string fileExtension);
    MapLoader(
        std::string resourceLocation,
        std::string fileExtension,
        uint_fast8_t maxTileMaps
    );
    std::vector<mapData> loadTileMaps(
        gameDataRef gameData,
        const sf::Vector2f& position,
        const sf::Vector2f& size
    );
    bool isMapLayoutValid(std::string fileName);
    std::vector<std::vector<std::string>> loadMapLayout(std::string fileName);
    void setFileExtension(std::string extension);
    void setResourceLocation(std::string location);
};

#endif // __MAPLOADER_HPP__

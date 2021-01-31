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

typedef struct {std::string name; TileMap tileMap;} mapData;

/// \brief
/// Class MapLoader
/// \details
/// MapLoader is a class that lets MapSelectorState load in a map/maps.
class MapLoader {
private:
    std::string resourceLocation;
    std::string fileExtension;
    uint_fast8_t maxTileMaps;
public:
    /// \brief
    /// MapLoader default constructor
    /// \details
    /// Empty default constructor that loads map from Resource::mapFolderLocation (default "resources/maps").
    MapLoader();
    
    /// \brief
    /// MapLoader overloaded constructor
    /// \details
    /// Constructor that you need to give a resourceLocation.
    /// It will take fileExtention and maxTileMaps from Resource:: (default ".txt" and 5u)
    MapLoader(std::string resourceLocation);
    
    /// \brief
    /// MapLoader overloaded constructor
    /// \details
    /// Constructor that you need to give a resourceLocation and a fileExtention.
    /// It will take maxTileMaps from Resource:: (default 5u)
    MapLoader(std::string resourceLocation, std::string fileExtension);
    
    /// \brief
    /// MapLoader overloaded constructor
    /// \details
    /// Constructor that you need to give a resourceLocation, a fileExtention and a maxTileMaps.
    /// This constructor will not take anything from Resource::   
    MapLoader(
        std::string resourceLocation,
        std::string fileExtension,
        uint_fast8_t maxTileMaps
    );
    
    /// \brief
    /// std::vector<mapData> loadTileMaps(gameDataRef gameData, const sf::Vector2f& position, const sf::Vector2f& size)
    /// \details
    /// This function check all files in given resourceLocation with given fileExtensions up to the maxTileMaps.
    /// It will validate these functions based on these parameters and on if the contents of the file is valid.
    /// If all checks out it will make a TileMap based on the given file(s) and put it in a std::vector<mapData>, wich it returns.
    std::vector<mapData> loadTileMaps(
        gameDataRef gameData,
        const sf::Vector2f& position,
        const sf::Vector2f& size
    );

    /// \brief
    /// bool isMapLayoutValid(std::string fileName)
    /// \details
    /// This function will check if a given file corresponds to the format.
    /// A file is valid if it contains non but the following:
    ///     -5 letter words seperated by spaces
    ///     -All words must be either ""solid", "break", "empty" or "spawn"
    /// If this is the case it will return true.
    bool isMapLayoutValid(std::string fileName);

    /// \brief
    /// std::vector<std::vector<std::string>> loadMapLayout(std::string fileName)
    /// \details
    /// Function will transform a given file into std::vector<std::vector<std::string>>.
    /// It should be called once the file is already checked to be valid.
    /// It takes all words in a line an puts them in the vector<string>.
    /// It will then put all lines into another vector.
    std::vector<std::vector<std::string>> loadMapLayout(std::string fileName);

    /// \brief
    /// void setFileExtension(std::string extension)
    /// \details
    /// If you want to change the file extension half way through using the same instance of this class you can.
    /// Simply give this function the (new) extention.
    void setFileExtension(std::string extension);

    /// \brief
    /// void setResourceLocation(std::string location)
    /// \details
    /// If you want to change the folder location half way through using the same instance of this class you can.
    /// Simply give this function the (new) location.
    void setResourceLocation(std::string location);
};

#endif // __MAPLOADER_HPP__

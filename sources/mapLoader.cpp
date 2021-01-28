#include "../headers/mapLoader.hpp"
#include "../headers/definitions.hpp"

MapLoader::MapLoader():
    MapLoader{Resource::mapFolderLocation}
{}

MapLoader::MapLoader(std::string resourceLocation):
    MapLoader{resourceLocation, Resource::fileExtension, Resource::maxTileMaps}
{}

MapLoader::MapLoader(std::string resourceLocation, std::string fileExtension):
    MapLoader{resourceLocation, fileExtension, Resource::maxTileMaps}
{}

MapLoader::MapLoader(
    std::string resourceLocation,
    std::string fileExtension,
    uint_fast8_t maxTileMaps
):
    resourceLocation{resourceLocation},
    fileExtension{fileExtension},
    maxTileMaps{maxTileMaps}
{}

std::vector<mapData> MapLoader::loadTileMaps(
    gameDataRef gameData,
    const sf::Vector2f& position,
    const sf::Vector2f& size
) {
    std::vector<mapData> maps;
    uint_fast8_t loadedTileMaps{};
    using directoryIterator = std::experimental::filesystem::directory_iterator;

    for (const auto& entry : directoryIterator(resourceLocation)) {
        if (entry.path().extension().string() not_eq fileExtension) {
            continue;
        }
        if (not isMapLayoutValid(entry.path().string())) {
            continue;
        }
        if (++loadedTileMaps > maxTileMaps) {
            break;
        }
        maps.emplace_back(mapData{
            entry.path().filename().replace_extension().string(),
            TileMap{gameData, position, size, loadMapLayout(entry.path().string())}
        });
    }
    return maps;
}

std::vector<std::vector<std::string>> MapLoader::loadMapLayout(std::string fileName) {
    std::vector<std::vector<std::string>> map;
    std::ifstream file{fileName};
    std::string line;

    while (getline(file, line)) {
        std::vector<std::string> mapLine;
        std::istringstream stream{line};
        std::string word;

        while (stream >> word) {
            mapLine.push_back(word);
        }
        map.push_back(mapLine);
    }
    file.close();
    return map;
}

bool MapLoader::isMapLayoutValid(std::string fileName) {
    std::ifstream file{fileName};
    std::string line;

    while (getline(file, line)) {
        std::istringstream stream{line};
        std::string word;

        while (stream >> word) {
            if (word not_eq "solid"
            and word not_eq "break"
            and word not_eq "empty"
            and word not_eq "spawn"
            ) {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return true;
}

void MapLoader::setFileExtension(std::string extension) {
    fileExtension = extension;
}

void MapLoader::setResourceLocation(std::string location) {
    resourceLocation = location;
}

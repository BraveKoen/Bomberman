#ifndef __MAPSELECTORSTATE_HPP__
#define __MAPSELECTORSTATE_HPP__

#include "state.hpp"
#include "game.hpp"
#include "tileMap.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MapSelectorState : public State{
public:
    MapSelectorState(gameDataRef gameData);

    void init();
    void handleInput();
    void update(float deltaTime);
    void draw(float deltaTime);
private:
    gameDataRef gameData;
    int mapToDisplayIndex;
    std::vector<sf::Text> menuOptionsText;
    sf::Sprite background;
    std::vector<sf::Sprite> menuOptions;
    std::vector<std::string> mapNames;
    std::vector<TileMap> tileMapVector;  

    bool MapSelectorState::isValidFile(std::string fileName);
    std::vector<std::vector<std::string>> MapSelectorState::makeMap(std::string fileName);
    void MapSelectorState::spawnMapButtons();
};

#endif // __MAPSELECTORSTATE_HPP__
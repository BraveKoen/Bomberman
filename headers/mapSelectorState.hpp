#ifndef __MAPSELECTORSTATE_HPP__
#define __MAPSELECTORSTATE_HPP__

#include "state.hpp"
#include "game.hpp"
#include "tileMap.hpp"
#include "drawTileMap.hpp"
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
    sf::Sprite playButton;
    std::vector<sf::Sprite> menuOptions;
    std::vector<std::string> mapNames;
    std::vector<TileMap> tileMapVector;  

    bool isValidFile(std::string fileName);
    std::vector<std::vector<std::string>> makeMap(std::string fileName);
    void spawnMapButtons();
};

#endif // __MAPSELECTORSTATE_HPP__
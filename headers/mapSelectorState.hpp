#ifndef __MAPSELECTORSTATE_HPP__
#define __MAPSELECTORSTATE_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>
// #include <stdio.h>

#include "definitions.hpp"
#include "mapLoader.hpp"
#include "inGameState.hpp"
#include "tileMap.hpp"
#include "state.hpp"
#include "game.hpp"

class MapSelectorState : public State {
public:
    MapSelectorState(gameDataRef gameData);

    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float deltaTime) override;
    virtual void draw(float deltaTime) override;
private:
    gameDataRef gameData;
    MapLoader mapLoader;
    std::size_t selectedMapIndex;
    std::vector<sf::Text> menuOptionsText;
    sf::Sprite background;
    sf::Sprite playButton;
    sf::Text playButtonText;
    sf::Sprite returnButton;
    sf::Text returnButtonText;
    sf::Sprite playButtonMultiplayer;
    sf::Text playButtonMultiplayerText;
    std::vector<sf::Sprite> menuOptions;
    std::vector<mapData> mapStore;
    bool tileMapPreviewAvailable;

    void spawnMapButtons();
};

#endif // __MAPSELECTORSTATE_HPP__
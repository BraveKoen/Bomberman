#ifndef __MAPSELECTORSTATE_HPP__
#define __MAPSELECTORSTATE_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <experimental/filesystem>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "mapLoader.hpp"
#include "inGameState.hpp"
#include "tileMap.hpp"
#include "state.hpp"
#include "game.hpp"

/// \brief
/// Class MapSelectorState
/// \details
/// MapSelectorState is a public State.
/// Class will display a menu in wich a player can select a map to play.
class MapSelectorState : public State {
public:
    /// \brief
    /// MapSelectorState constructor
    /// \details
    /// This constructor needs a gameDataRef to work
    MapSelectorState(gameDataRef gameData);

    /// \brief
    /// virtual void init() override
    /// \details
    /// This function handles the creation of all visual elements the player sees.
    /// After making the background it will use the MapLoader and private function spawnMapButtons() to make the maps and spawn the corresponding buttons.
    /// It will then create a return button, a playButton and a playButtonMultiplayer (only one of the last two will be drawen based on what version is played). 
    virtual void init() override;

    /// \brief
    /// virtual void handleInput() override
    /// \details
    /// This function handles the click actions on all available buttons.
    /// When one of the buttons corresponding to one of the maps is clicked the previeuw will change and the map will be saved as the selected map.
    /// When the playButton or playButtonMultiplayer are clicked they will start the game (each in their own respective ways).
    /// When the backButton is pressed the MapSelectorState will be popped from the stack leading the player back to the main menu.
    /// When the window is closed the program will be terminated.
    virtual void handleInput() override;

    /// \brief
    /// virtual void update(float deltaTime) override
    /// \details
    /// This function will only perform actions if the player is playing online multiplayer.
    /// If so, the function will join the threads and put a InGameState on the stack.
    virtual void update(float deltaTime) override;

    /// \brief
    /// virtual void draw(float deltaTime) override
    /// \details
    /// This function draws all created objects on the screen if and when necessary.
    virtual void draw(float deltaTime) override;

    /// \brief
    /// void lobbyQueue()
    /// \details
    /// This function lets non host players join and turns the startGame to true, 
    /// causing the update function to be able to start the game. 
    void lobbyQueue();
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
    std::vector<std::string> mapNames;
    std::vector<TileMap> tileMapVector;  
    std::thread mThread;
    bool startGame = false;

    void spawnMapButtons();
};

#endif // __MAPSELECTORSTATE_HPP__
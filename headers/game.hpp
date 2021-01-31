#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include "definitions.hpp"
#include "stateMachine.hpp"
#include "assetManager.hpp"
#include "inputManager.hpp"
#include "tileMap.hpp"
#include "server.hpp"

struct GameData{
    sf::RenderWindow window;
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    TileMap tileMap;
    unsigned int playerCount;
    Server server{Resource::serverIp, 1999};
    bool multiplayer;
};

/// \brief
/// Game class
/// \details
/// The Game class should be the only thing that needs to be made in the main function.
/// After calling the constructor it will call it's own run() function which will start the game loop and continue running it until the window/game is closed.
/// In the game loop this class will call the handleInput, update and draw functions for the current state.
class Game{
private:
    gameDataRef gameData;
    const float delta;
    sf::Clock clock;

    void run();
public:
    /// \brief
    /// Constructor for the Game class
    /// \details
    /// Takes int width and int height for the screen dimentions, as well as a std::string title for the window.
    /// The constructor calls it's own run() function, which will start the game loop until the game is closed.
    Game(int width, int height, std::string title);
};

#endif // __GAME_HPP__

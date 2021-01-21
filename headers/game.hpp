#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "stateMachine.hpp"
#include "assetManager.hpp"
#include "inputManager.hpp"
#include "tileMap.hpp"

struct GameData{
    sf::RenderWindow window;
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    TileMap tileMap;
    int playerCount;
};

class Game{
    private:
        gameDataRef gameData;
        const float delta;
        sf::Clock clock;

        void run();
    public:
        Game(int width, int height, std::string title);
};

#endif // __GAME_HPP__

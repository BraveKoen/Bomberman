#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "stateMachine.hpp"
#include "assetManager.hpp"
#include "inputManager.hpp"
#include "tileMap.hpp"
#include "definitions.hpp"

struct GameData{
    sf::RenderWindow window;
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    TileMap tileMap;
    int playerCount = 1;
};

typedef std::shared_ptr<GameData> gameDataRef;

class Game{
    private:
        const float delta = 1.0f / 60.0f;
        sf::Clock clock;
        gameDataRef gameData = std::make_shared<GameData>();

        void run();
    public:
        Game(int width, int height, std::string title);
};

#endif // __GAME_HPP__

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../headers/stateMachine.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/inputManager.hpp"
#include "../headers/tileMap.hpp"

struct GameData{
    sf::RenderWindow window;
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    TileMap tileMap;
    int playerCount = 1;
};

using gameDataRef = std::shared_ptr<GameData>;

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

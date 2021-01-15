#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <memory>
#include "../headers/assetManager.hpp"
#include "../headers/inputManager.hpp"

struct GameData {
    // StateMachine machine;
    sf::RenderWindow window;
    AssetManager assetManager;
    InputManager inputManager;
};

using gameDataRef = std::shared_ptr<GameData>;

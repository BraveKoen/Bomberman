#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <memory>
#include "input-manager.hpp"

struct GameData {
    // StateMachine machine;
    sf::RenderWindow window;
    // AssetManager assets;
    InputManager inputManager;
};

using gameDataRef = std::shared_ptr<GameData>;

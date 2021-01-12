#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>

class InputManager {
public:
    InputManager();
    auto isSpriteClicked(
        sf::Sprite sprite,
        sf::Mouse::Button button,
        sf::RenderWindow &window
    ) const -> bool;
    auto getMousePosition(
        sf::RenderWindow &window
    ) const -> sf::Vector2i;
};

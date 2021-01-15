#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "../headers/inputManager.hpp"

InputManager::InputManager() {}

auto InputManager::isSpriteClicked(
    sf::Sprite sprite,
    sf::Mouse::Button button,
    sf::RenderWindow& window
) const -> bool {
    return sf::Mouse::isButtonPressed(button)
        and sprite.getGlobalBounds().contains(getMousePosition(window));
}

auto InputManager::getMousePosition(
    sf::RenderWindow &window
) const -> sf::Vector2f {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
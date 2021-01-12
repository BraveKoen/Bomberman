#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "input-manager.hpp"

InputManager::InputManager() {}

auto InputManager::isSpriteClicked(
    sf::Sprite sprite,
    sf::Mouse::Button button,
    sf::RenderWindow& window
) const -> bool {
    return sf::Mouse::isButtonPressed(button)
        and sprite.getGlobalBounds().contains(
            window.mapPixelToCoords(getMousePosition(window)));
}

auto InputManager::getMousePosition(
    sf::RenderWindow &window
) const -> sf::Vector2i {
    return sf::Mouse::getPosition(window);
}

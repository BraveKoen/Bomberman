#include "../headers/inputManager.hpp"

sf::Vector2f InputManager::getMousePosition(const sf::RenderWindow& window) const {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::Vector2i InputManager::getMousePositionInt(const sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}

bool InputManager::isSpriteClicked(
    const sf::Sprite& object,
    const sf::Mouse::Button& button,
    const sf::RenderWindow& window
) const {
    return sf::Mouse::isButtonPressed(button)
        && object.getGlobalBounds().contains(getMousePosition(window));
}

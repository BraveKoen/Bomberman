#include "../headers/InputManager.hpp"

sf::Vector2f InputManager::getMousePosition(sf::RenderWindow & window){
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

sf::Vector2i InputManager::getMousePositionInt(sf::RenderWindow & window){
    return sf::Mouse::getPosition(window);
}

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window){
    return sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains(getMousePosition(window));
}
#include "../headers/InputManager.hpp"

sf::Vector2f InputManager::getMousePosition(sf::RenderWindow & window){
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    return sf::Vector2f(static_cast< float >( pos.x ), static_cast< float >( pos.y ));
}

sf::Vector2i InputManager::getMousePositionInt(sf::RenderWindow & window){
    return sf::Mouse::getPosition(window);
}

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window){
    return sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains(getMousePosition(window));
}
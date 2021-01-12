#include "../headers/InputManager.hpp"

sf::Vector2f InputManager::GetMousePosition(sf::RenderWindow & window){
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    return sf::Vector2f(static_cast< float >( pos.x ), static_cast< float >( pos.y ));
}

sf::Vector2i InputManager::GetMousePositionInt(sf::RenderWindow & window){
    return sf::Mouse::getPosition(window);
}

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window){
    return sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains(GetMousePosition(window));
}
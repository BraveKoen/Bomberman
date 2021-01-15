#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__

#include <SFML/Graphics.hpp>

class InputManager{
private:
public:
    sf::Vector2f getMousePosition(const sf::RenderWindow& window) const;
    sf::Vector2i getMousePositionInt(const sf::RenderWindow& window) const;
    bool isSpriteClicked(const sf::Sprite& object, const sf::Mouse::Button& button, const sf::RenderWindow& window) const;
};

#endif // __INPUTMANAGER_HPP__

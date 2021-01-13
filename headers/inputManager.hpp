#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__

#include <SFML/Graphics.hpp>

class InputManager{
    private:
    public:
        sf::Vector2f getMousePosition(sf::RenderWindow & window);
        sf::Vector2i getMousePositionInt(sf::RenderWindow & window);
        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window);
};

#endif // __INPUTMANAGER_HPP__

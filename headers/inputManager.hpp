#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__

#include <SFML/Graphics.hpp>

class InputManager{
    private:
    public:
        sf::Vector2f GetMousePosition(sf::RenderWindow & window);
        sf::Vector2i GetMousePositionInt(sf::RenderWindow & window);
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window);
};

#endif // __INPUTMANAGER_HPP__

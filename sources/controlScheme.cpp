#include "../headers/controlScheme.hpp"

ControlScheme::ControlScheme(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key bombKey): //Keys ordered in standard WASD format, with the extra bomb key at the end
    upKey(upKey),
    leftKey(leftKey),
    downKey(downKey),
    rightKey(rightKey),
    bombKey(bombKey)
    {}

sf::Vector2i ControlScheme::getDirection() const{
        int x=0;
        int y=0;
        if(sf::Keyboard::isKeyPressed(upKey))       y--;
        if(sf::Keyboard::isKeyPressed(leftKey))     x--;
        if(sf::Keyboard::isKeyPressed(downKey))     y++;
        if(sf::Keyboard::isKeyPressed(rightKey))    x++;
        return sf::Vector2i(x,y);
}

bool ControlScheme::getBombKeyPressed() const{
    return sf::Keyboard::isKeyPressed(bombKey);
}
#ifndef __CONTROLSCHEME_HPP__
#define __CONTROLSCHEME_HPP__

#include <SFML/Graphics.hpp>

class ControlScheme{
private:
    sf::Keyboard::Key upKey, leftKey, downKey, rightKey, bombKey;
public:
    ControlScheme(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key bombKey); //Keys ordered in standard WASD format, with the extra bomb key at the end

    sf::Vector2i getDirection() const;
    bool getBombKeyPressed() const;
};

#endif // __CONTROLSCHEME_HPP__
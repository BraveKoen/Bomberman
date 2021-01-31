#ifndef __CONTROLSCHEME_HPP__
#define __CONTROLSCHEME_HPP__

#include <SFML/Graphics.hpp>

/// \brief
/// Simple class for creating basic control schemes.
/// \details
/// This class is mainly meant for having multiple control schemes on the same client, i.e. local multiplayer wih people using WASD, IJKL and arrow keys for example.
/// Currently the class is made specifically for bomberman and only support movement keys and a bomb key, but it can very easily be expanded/changed to, for example, include an 'interaction' key.
class ControlScheme{
private:
    sf::Keyboard::Key upKey, leftKey, downKey, rightKey, bombKey;
public:
    /// \brief
    /// ControlScheme constructor
    /// \details
    /// ControlSCheme construction, takes sf::Keyboard::key for every input (movement directions + bomb placement).
    ControlScheme(sf::Keyboard::Key upKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key downKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key bombKey); //Keys ordered in standard WASD format, with the extra bomb key at the end

    /// \brief
    /// Returns the movement direction
    /// \details
    /// Returns the movement direction based on which of the directional input keys are pressed. Returns the direction of the movement as a vector with amplitude 1.
    sf::Vector2i getDirection() const;

    /// \brief
    /// Returns wether the bomb key is pressed.
    /// \details
    /// Returns wether the given (in the constructor) bomb key is pressed.
    bool getBombKeyPressed() const;
};

#endif // __CONTROLSCHEME_HPP__
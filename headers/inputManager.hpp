#ifndef __INPUTMANAGER_HPP__
#define __INPUTMANAGER_HPP__

#include <SFML/Graphics.hpp>

/// \brief
/// Class for managing user input
/// \details
/// This class is meant to manage all user input, wether that be mouse clicks or button presses.
/// Currently it only has a couple of mouse related functions of which the isSpriteClicked function is used most commonly.
/// It would however be super simple to add a function that, say, handles button presses.
class InputManager{
public:
    /// \brief
    /// Mouse position getter
    /// \details
    /// Returns the position of the mouse in the given window as an sf::Vector2f.
    sf::Vector2f getMousePosition(const sf::RenderWindow& window) const;

    /// \brief
    /// Mouse position getter
    /// \details
    /// Returns the position of the mouse in the given window as an sf::Vector2i.
    sf::Vector2i getMousePositionInt(const sf::RenderWindow& window) const;

    /// \brief
    /// Simple mouse <-> sprite collision
    /// \details
    /// Returns wether the mouse is over the given sprite in the given window when the given mousebutton is pressed.
    bool isSpriteClicked(
        const sf::Sprite& object,
        const sf::Mouse::Button& button,
        const sf::RenderWindow& window
    ) const;
};

#endif // __INPUTMANAGER_HPP__

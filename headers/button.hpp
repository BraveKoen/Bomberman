#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <SFML/Graphics.hpp>

#include "definitions.hpp"

/// \brief
/// Abstract Button class
/// \details
/// The Button class is an abstract class that stores a sprite and a text
/// object to represent the appearance of a button and it provies the
/// interface for the drawing and interaction mechanics.
class Button {
private:
    sf::Sprite sprite;
    sf::Text text;
public:
    /// \brief
    /// Constructor for lvalue sprites and texts
    /// \details
    /// Receives a sprite object used for drawing and interaction and a text
    /// object to display a text message on the button.
    Button(const sf::Sprite& sprite, const sf::Text& text);
    /// \brief
    /// Constructor for rvalue sprites and texts
    /// \details
    /// Receives a sprite object used for drawing and interaction and a text
    /// object to display a text message on the button.
    Button(sf::Sprite&& sprite, sf::Text&& text);

    /// \brief
    /// Getter for the sprite object
    /// \details
    /// Return the stored sprite object
    virtual const sf::Sprite& getSprite() const;
    /// \brief
    /// Draws objects onto the given window
    /// \details
    /// Draws the sprite and text object onto given window object.
    virtual void draw(sf::RenderWindow& window) const;
    /// \brief
    /// Invokes an action
    /// \details
    /// Meant providing the implementation for invoking an action whenever the
    /// user interacts with the button. Receives an GameData object.
    virtual void invokeAction(gameDataRef gameData) const = 0;
};

#endif // __BUTTON_HPP__

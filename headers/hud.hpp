#ifndef __HUD_HPP__
#define __HUD_HPP__

#include <SFML/Graphics.hpp>

/// \brief
/// HUD class
/// \details
/// The base class for creating and drawing HUD objects onto the screen.
/// Stores a frame object and provides the drawing implementation thereof.
class HUD {
protected:
    sf::Sprite frame;
public:
    HUD() = default;
    /// \brief
    /// Getter for the frame width
    /// \details
    /// Returns the width of the frame sprite object.
    float getFrameWidth() const;
    /// \brief
    /// Getter for the frame height
    /// \details
    /// Returns the height of the frame sprite object.
    float getFrameHeight() const;
    /// \brief
    /// Getter for the frame size
    /// \details
    /// Returns the size of the frame object as a floating point vector.
    sf::Vector2f getFrameSize() const;
    /// \brief
    /// Setter for the frame scale
    /// \details
    /// Sets the scale of the frame object.
    void setFrameScale(float factorX, float factorY);
    /// \brief
    /// Provides drawing
    /// \details
    /// Draws the frame object onto the specified window and calls the
    /// drawImplementation() function, using the NVI pattern.
    virtual void draw(sf::RenderWindow& window) const;
    /// \brief
    /// Draws additional objects onto the window
    /// \details
    /// Meant for providing the implementation for drawing additional objects
    /// onto the specified window, following the NVI pattern.
    virtual void drawImplementation(sf::RenderWindow& window) const = 0;
};

#endif // __HUD_HPP__

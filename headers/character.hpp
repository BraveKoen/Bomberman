#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "bombHandler.hpp"

/// \brief
/// Pure virtual base character class
/// \details
/// This class is meant to be a base class for player and opponent, but due to time limits and stuff it ended up remaining pure virtual.
class Character {
public:
    /// \brief
    /// Default constructor
    /// \details
    /// Default constructor for Character class
    Character() = default;

    /// \brief
    /// Pure virtual draw function
    /// \details
    /// Pure virtual draw function for Character class
    virtual void draw() = 0;

    /// \brief
    /// Pure virtual setHealth function
    /// \details
    /// Pure virtual health setter for Character class
    virtual void setHealth(uint8_t health) = 0;

    /// \brief
    /// Pure virtual getHealth function
    /// \details
    /// Pure virtual health getter for Character class
    virtual int getHealth() const = 0;
    
    /// \brief
    /// Pure virtual setPosition function
    /// \details
    /// pure virtual position getter for Character class
    virtual void setPosition(const sf::Vector2f& pos) = 0;

    /// \brief
    /// Pure virtual getPosition function
    /// \details
    /// Pure virtual position getter for Character class
    virtual const sf::Vector2f& getPosition() const = 0;

    /// \brief
    /// Pure virtual setMovementSpeed function
    /// \details
    /// Pure virtual movementSpeed setter for Character class
    virtual void setMovementSpeed(uint8_t speed) = 0;

    /// \brief
    /// Pure virtual getMovementSpeed function
    /// \details
    /// Pure virtual movementSpeed getter for Character class
    virtual int getMovementSpeed() const = 0;

    /// \brief
    /// Pure virtual getPlayerId function
    /// \details
    /// Pure virtual pllayerId getter for Character class
    virtual unsigned int getPlayerId() const = 0;

    /// \brief
    /// Pure virtual isPlayerAlive function
    /// \details
    /// Pure virtual playerAlive getter for Character class
    virtual bool isPlayerAlive() const = 0;
};

#endif // __CHARACTER_HPP__
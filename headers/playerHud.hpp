#ifndef __PLAYERHUD_HPP__
#define __PLAYERHUD_HPP__

#include <array>
#include <SFML/Graphics.hpp>
#include "hud.hpp"
#include "definitions.hpp"

class PlayerHUD : public HUD {
private:
    sf::Sprite profile;
    std::array<sf::Sprite, Resource::HUD::maxLives> healthBar;
    void createHealthBar(gameDataRef gameData, sf::Vector2f&& position);
public:
    /// \brief
    /// Constructor for PlayerHUD
    /// \details
    /// Creates a player HUD based on playerId, at positon with maxWidth.
    PlayerHUD(
        gameDataRef gameData,
        uint_fast8_t playerId,
        const sf::Vector2f& position,
        float maxWidth
    );

    /// \brief
    /// Setter for healthbar
    /// \details
    /// This function allows you to set how many of the lives on the health bar need to be full or empty.
    void setHealthBar(gameDataRef gameData, uint_fast8_t lives);

    /// \brief
    /// Draws player HUD
    /// \details
    /// This function draws all of the screen objects in the player HUD
    virtual void drawImplementation(sf::RenderWindow& window) const override;
};

#endif // __PLAYERHUD_HPP__

#ifndef __GAMEHUD_HPP__
#define __GAMEHUD_HPP__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "hud.hpp"
#include "playerHud.hpp"
#include "definitions.hpp"

/// \brief
/// Derived GameHud class
/// \details
/// Provides the implementation of the Game HUD. Controls a number of Player
/// HUDs based on the playerCount variable from a GameData object. Allows for
/// individual drawing of Player HUDs based on a playerId.
class GameHUD : public HUD {
private:
    sf::Sprite banner;
    std::vector<PlayerHUD> playerHuds;

    /// \brief
    /// Creates Player HUDs
    /// \details
    /// Creates a number of Player HUDs based on the playerCount variable from
    /// GameData object. The position refers to the top-left position of where
    /// a Player HUD should be drawn.
    void createPlayerHuds(gameDataRef gameData, sf::Vector2f&& position);
public:
    /// \brief
    /// Constructs a GameHUD object
    /// \details
    /// Constructs a GameHUD object with a default top left position of {0, 0}.
    GameHUD(gameDataRef gameData);
    /// \brief
    /// Constructs a GameHUD object
    /// \details
    /// Constructs a GameHUD object, the position refers to a top-left point.
    GameHUD(gameDataRef gameData, const sf::Vector2f& position);
    /// \brief
    /// Sets the number of lives of a health bar
    /// \details
    /// Sets the number of lives that a health bar of a specific player should
    /// draw based on a given playerId. The count of playerIds starts with 1,
    /// so it's important not to pass along a value of 0.
    void setHealthBar(gameDataRef gameData, uint_fast8_t playerId, uint_fast8_t lives);
    /// \brief
    /// Draws objects onto the specified window
    /// \details
    /// Draws all of its objects onto the specified window. This includes the
    /// the banner and all of the PlayerHUDs that were created during the
    /// construction of this object.
    virtual void drawImplementation(sf::RenderWindow& window) const override;
    /// \brief
    /// Draws the frame onto the specified window
    /// \details
    /// Only draws the frame and the banner onto specified window. Does not
    /// draw any of the Player HUD objects. This might not have been the best
    /// function name but that's what happens when time is short.
    void drawFrame(sf::RenderWindow& window) const;
    /// \brief
    /// Draws a Player HUD
    /// \details
    /// Draws a specific Player HUD onto the provided window object based on
    /// a playerId. The counting of the playerIds starts at 1 instead of 0.
    void drawPlayerHud(sf::RenderWindow& window, uint_fast8_t playerId ) const;
};

#endif // __GAMEHUD_HPP__

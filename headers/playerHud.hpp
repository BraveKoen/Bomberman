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
    PlayerHUD(
        gameDataRef gameData,
        uint_fast8_t playerId,
        const sf::Vector2f& position,
        float maxWidth
    );
    void setHealthBar(gameDataRef gameData, uint_fast8_t lives);
    virtual void drawImplementation(sf::RenderWindow& window) const override;
};

#endif // __PLAYERHUD_HPP__

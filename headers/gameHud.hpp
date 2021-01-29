#ifndef __GAMEHUD_HPP__
#define __GAMEHUD_HPP__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "hud.hpp"
#include "playerHud.hpp"
#include "definitions.hpp"

class GameHUD : public HUD {
private:
    sf::Sprite banner;
    std::vector<PlayerHUD> playerHuds;
    void createPlayerHuds(gameDataRef gameData, sf::Vector2f&& position);
public:
    GameHUD(gameDataRef gameData);
    GameHUD(gameDataRef gameData, const sf::Vector2f& position);
    void setHealthBar(gameDataRef gameData, uint_fast8_t playerId, uint_fast8_t lives);
    virtual void drawImplementation(sf::RenderWindow& window) const override;
    void drawFrame(sf::RenderWindow& window) const;
    void drawPlayerHud(sf::RenderWindow& window, uint_fast8_t playerId ) const;
};

#endif // __GAMEHUD_HPP__

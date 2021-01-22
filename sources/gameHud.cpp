#include "../headers/hud.hpp"
#include "../headers/gameHud.hpp"
#include "../headers/playerHud.hpp"
#include "../headers/mainMenuState.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

GameHUD::GameHUD(gameDataRef gameData):
    GameHUD{gameData, {0, 0}}
{}

GameHUD::GameHUD(gameDataRef gameData, const sf::Vector2f& position):
    HUD{gameData->assetManager.getTexture("HUD frame")},
    banner{gameData->assetManager.getTexture("HUD banner")}
{
    constexpr auto ratio = 17/20.f;
    const auto windowHeight = gameData->window.getSize().y;
    frame.setScale(1, Util::scaleFromRatio(windowHeight, getFrameHeight(), ratio));
    frame.setPosition(position);

    const auto frameWidth = getFrameWidth();
    const auto borderX = position.x + Util::offsetFromRatio(frameWidth, ratio);
    const auto borderY = position.y + 12;
    banner.setPosition(borderX, borderY);
    banner.setScale(Util::scaleFromRatio(frameWidth, Sprite::getWidth(banner), ratio), 1);
    createPlayerHuds(gameData, {position.x, borderY + Sprite::getHeight(banner)});
    // add optional game time here
}

void GameHUD::createPlayerHuds(gameDataRef gameData, sf::Vector2f&& position) {
    for (auto index = 0u; index < gameData->playerCount; ++index) {
        static const auto maxWidth = getFrameWidth();
        playerHuds.emplace_back(gameData, index, position, maxWidth);
        static const auto& hudSize = playerHuds[index].getFrameSize();
        position.y += hudSize.y;
    }
}

void GameHUD::setHealthBar(gameDataRef gameData, uint_fast8_t playerId, uint_fast8_t lives) {
    playerHuds[playerId].setHealthBar(gameData, lives);
}

void GameHUD::drawImplementation(sf::RenderWindow& window) const {
    window.draw(banner);

    for (const auto& playerHud : playerHuds) {
        playerHud.draw(window);
    }
}

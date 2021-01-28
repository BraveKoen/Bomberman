#include "../headers/hud.hpp"
#include "../headers/gameHud.hpp"
#include "../headers/playerHud.hpp"
#include "../headers/mainMenuState.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

GameHUD::GameHUD(gameDataRef gameData):
    GameHUD{gameData, {0, 0}}
{}

GameHUD::GameHUD(gameDataRef gameData, const sf::Vector2f& position) {
    Util::loadTextures(gameData, std::array{
        resourceContainer{Resource::HUD::mainFrame, &frame},
        resourceContainer{Resource::HUD::banner, &banner}
    });
    constexpr auto ratio = 85/100.f;
    const auto windowHeight = gameData->window.getSize().y;
    frame.setScale(Util::yScaleFromRatio(windowHeight, getFrameHeight(), 1));
    frame.setPosition(position);

    const auto frameWidth = getFrameWidth();
    const auto borderX = position.x + Util::offsetFromRatio(frameWidth, ratio);
    const auto borderY = position.y + 12;
    banner.setPosition(borderX, borderY);
    const auto bannerScale = Util::scaleFromRatio(frameWidth, Util::getWidth(banner), ratio);
    banner.setScale(bannerScale, bannerScale);
    createPlayerHuds(gameData, {position.x, borderY + Util::getHeight(banner)});
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
    playerHuds[playerId - 1].setHealthBar(gameData, lives);
}

void GameHUD::drawImplementation(sf::RenderWindow& window) const {
    window.draw(banner);

    for (const auto& playerHud : playerHuds) {
        playerHud.draw(window);
    }
}

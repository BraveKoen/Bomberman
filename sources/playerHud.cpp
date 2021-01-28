#include "../headers/hud.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/playerHud.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

PlayerHUD::PlayerHUD(
    gameDataRef gameData,
    uint_fast8_t playerId,
    const sf::Vector2f& position,
    float maxWidth
) {
    Util::loadTextures(gameData, std::array{
        resourceContainer{Resource::HUD::subFrame, &frame},
        resourceContainer{Resource::HUD::profiles[playerId % Resource::HUD::maxPlayers], &profile},
        resourceContainer{Resource::HUD::fullLife},
        resourceContainer{Resource::HUD::emptyLife}
    });
    constexpr auto ratio = 90/100.f;
    const auto borderX = position.x + Util::offsetFromRatio(maxWidth, ratio);
    frame.setScale(Util::xScaleFromRatio(maxWidth, getFrameWidth(), ratio));
    frame.setPosition(borderX, position.y);

    const auto frameWidth = getFrameWidth();
    const auto borderY = position.y + 12;
    profile.setScale(Util::xScaleFromRatio(frameWidth, Util::getWidth(profile), ratio));
    profile.setPosition(borderX + Util::offsetFromRatio(frameWidth, ratio), borderY);
    createHealthBar(gameData, {borderX, borderY + Util::getHeight(profile)});
}

void PlayerHUD::createHealthBar(gameDataRef gameData, sf::Vector2f&& position) {
    for (auto index = 0u; index < healthBar.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture(Resource::HUD::fullLife);
        healthBar[index].setTexture(texture);
        static const auto frameWidth = getFrameWidth();
        static const auto healthWidth = Util::getWidth(healthBar[index]);
        static const auto offset = Util::offsetFromContent(frameWidth, healthWidth * healthBar.size());
        healthBar[index].setPosition(position.x + offset, position.y);
        position.x += healthWidth;
    }
}

void PlayerHUD::setHealthBar(gameDataRef gameData, uint_fast8_t lives) {
    for (auto index = 0u; index < healthBar.size(); ++index) {
        if (index < lives) {
            static const auto& fullLife = gameData->assetManager.getTexture(Resource::HUD::fullLife);
            healthBar[index].setTexture(fullLife);
        } else {
            static const auto& emptyLife = gameData->assetManager.getTexture(Resource::HUD::emptyLife);
            healthBar[index].setTexture(emptyLife);
        }
    }
}

void PlayerHUD::drawImplementation(sf::RenderWindow& window) const {
    window.draw(profile);

    for (const auto& health : healthBar) {
        window.draw(health);
    }
}

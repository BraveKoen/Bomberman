#include "../headers/hud.hpp"
#include "../headers/playerHud.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

PlayerHUD::PlayerHUD(
    gameDataRef gameData,
    uint_fast8_t playerId,
    const sf::Vector2f& position,
    float maxWidth
):
    HUD{gameData->assetManager.getTexture("HUD small frame")}, 
    profile{gameData->assetManager.getTexture("HUD profile", playerId)}
{
    constexpr auto ratio = 9/10.f;
    const auto borderX = position.x + Util::offsetFromRatio(maxWidth, ratio);
    frame.setScale(Util::scaleFromRatio(maxWidth, getFrameWidth(), ratio), 1);
    frame.setPosition(borderX, position.y);

    const auto frameWidth = getFrameWidth();
    const auto borderY = position.y + 12;
    profile.setScale(Util::scaleFromRatio(frameWidth, Sprite::getWidth(profile), ratio), 1);
    profile.setPosition(borderX + Util::offsetFromRatio(frameWidth, ratio), borderY);
    createHealthBar(
        gameData->assetManager.getTexture("HUD live full"),
        {borderX, borderY + Sprite::getHeight(profile)}
    );
}

void PlayerHUD::createHealthBar(
    const sf::Texture& texture,
    sf::Vector2f&& position
) {
    for (auto index = 0u; index < healthBar.size(); ++index) {
        healthBar[index].setTexture(texture);
        static const auto frameWidth = getFrameWidth();
        static const auto healthWidth = Sprite::getWidth(healthBar[index]);
        static const auto offset = Util::offsetFromContent(frameWidth, healthWidth * healthBar.size());
        healthBar[index].setPosition(position.x + offset, position.y);
        position.x += healthWidth;
    }
}

void PlayerHUD::setHealthBar(gameDataRef gameData, uint_fast8_t lives) {
    for (auto index = 0u; index < healthBar.size(); ++index) {
        if (index < lives) {
            static const auto& full = gameData->assetManager.getTexture("HUD live full");
            healthBar[index].setTexture(full);
        } else {
            static const auto& empty = gameData->assetManager.getTexture("HUD live empty");
            healthBar[index].setTexture(empty);
        }
    }
}

void PlayerHUD::drawImplementation(sf::RenderWindow& window) const {
    window.draw(profile);

    for (const auto& health : healthBar) {
        window.draw(health);
    }
}

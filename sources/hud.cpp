#include "../headers/hud.hpp"

HUD::HUD(const sf::Texture& texture):
    frame{texture}
{}

float HUD::getFrameWidth() const {
    return frame.getGlobalBounds().width;
}

float HUD::getFrameHeight() const {
    return frame.getGlobalBounds().height;
}

sf::Vector2f HUD::getFrameSize() const {
    const auto& bounds = frame.getGlobalBounds();
    return {bounds.width, bounds.height};
}

void HUD::setFrameScale(float factorX, float factorY) {
    return frame.setScale(factorX, factorY);
}

void HUD::draw(sf::RenderWindow& window) const {
    window.draw(frame);
    drawImplementation(window);
}

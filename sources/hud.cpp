#include "../headers/hud.hpp"
#include "../headers/utilities.hpp"

float HUD::getFrameWidth() const {
    return Util::getWidth(frame);
}

float HUD::getFrameHeight() const {
    return Util::getHeight(frame);
}

sf::Vector2f HUD::getFrameSize() const {
    return Util::getSize(frame);
}

void HUD::setFrameScale(float factorX, float factorY) {
    return frame.setScale(factorX, factorY);
}

void HUD::draw(sf::RenderWindow& window) const {
    window.draw(frame);
    drawImplementation(window);
}

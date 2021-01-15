#include "../headers/button.hpp"

Button::Button(const sf::Sprite& sprite, const sf::Text& text):
    sprite{sprite},
    text{text}
{}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(text);
}

const sf::Sprite& Button::getSprite() const {
    return sprite;
}

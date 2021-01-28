#include "../headers/button.hpp"

Button::Button(const sf::Sprite& sprite, const sf::Text& text):
    sprite{sprite},
    text{text}
{}

Button::Button(sf::Sprite&& sprite, sf::Text&& text):
    sprite{std::move(sprite)},
    text{std::move(text)}
{}

const sf::Sprite& Button::getSprite() const {
    return sprite;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    window.draw(text);
}

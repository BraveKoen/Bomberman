#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <SFML/Graphics.hpp>

#include "definitions.hpp"

class Button {
private:
    sf::Sprite sprite;
    sf::Text text;
public:
    Button(const sf::Sprite& sprite, const sf::Text& text);
    Button(sf::Sprite&& sprite, sf::Text&& text);

    virtual const sf::Sprite& getSprite() const;
    virtual void draw(sf::RenderWindow& window) const;
    virtual void invokeAction(gameDataRef gameData) const = 0;
};

#endif // __BUTTON_HPP__

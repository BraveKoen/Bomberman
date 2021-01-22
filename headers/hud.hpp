#ifndef __HUD_HPP__
#define __HUD_HPP__

#include <SFML/Graphics.hpp>

class HUD {
protected:
    sf::Sprite frame;
public:
    HUD(const sf::Texture& texture);
    float getFrameWidth() const;
    float getFrameHeight() const;
    // const sf::FloatRect getFrameBounds() const;
    sf::Vector2f getFrameSize() const;
    void setFrameScale(float factorX, float factorY);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void drawImplementation(sf::RenderWindow& window) const = 0;
};

#endif // __HUD_HPP__

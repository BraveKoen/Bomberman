#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <SFML/Graphics.hpp>
#include <string>

class Tile{
private:
    std::string type;
    sf::Sprite sprite;
public:
    Tile(std::string type="empty", sf::Sprite sprite=sf::Sprite());

    void setType(std::string newType);
    const std::string& getType() const;
    void setTexture(const sf::Texture & newTexture);
    const sf::Texture* getTexture() const;
    void setPosition(const sf::Vector2f & newPosition);
    const sf::Vector2f& getPosition() const;
    void setScale(const sf::Vector2f & newScale);
    const sf::Vector2f& getScale() const;
    const sf::Vector2f getSize() const;
    const sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow & window) const;
};

#endif // __TILE_HPP__

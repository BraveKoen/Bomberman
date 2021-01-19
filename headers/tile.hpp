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
    std::string getType();
    void setTexture(const sf::Texture & newTexture);
    const sf::Texture* getTexture();
    void setPosition(const sf::Vector2f & newPosition);
    sf::Vector2f getPosition();
    void setScale(const sf::Vector2f & newScale);
    sf::Vector2f getScale();
    sf::Vector2f getSize();
    const sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow & window);
};

#endif // __TILE_HPP__

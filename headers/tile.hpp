#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <SFML/Graphics.hpp>
#include <string>

/// \brief
/// Tile class for TileMap
/// \details
/// This class is essentially a basic datatype for the tiles in a TileMap, it contains it's own sprite and a string for it's type.
/// The class has various getters and setters for freely and easily changing and getting the type and various aspects of the sprite.
class Tile{
private:
    std::string type;
    sf::Sprite sprite;
public:
    /// \brief
    /// Tile constructor
    /// \details
    /// Can be constructed completely empty, leaving it the basic "empty" type and a default sprite with !no texture! (<- avoid this). Otherwise a type can be specified, possibly along with a sprite. These attributes can also be set through various setters.
    Tile(std::string type="empty", sf::Sprite sprite=sf::Sprite());

    /// \brief
    /// Setter for tile type
    /// \details
    /// Allows you to set the type of the tile to a string newType.
    void setType(std::string newType);

    /// \brief
    /// Getter for tile type
    /// \details
    /// Returns the type of the tile.
    const std::string& getType() const;

    /// \brief
    /// Setter for tile texture
    /// \details
    /// Allows you to set the texture of the tile's sprite.
    void setTexture(const sf::Texture & newTexture);

    /// \brief
    /// Getter for tile texture
    /// \details
    /// Returns a const pointer to the tile's texture.
    const sf::Texture* getTexture() const;

    /// \brief
    /// Setter for tile position
    /// \details
    /// Allows you to set the tile's (sprite's) position.
    void setPosition(const sf::Vector2f & newPosition);

    /// \brief
    /// Getter for tile position
    /// \details
    /// Returns the tile position.
    const sf::Vector2f& getPosition() const;

    /// \brief
    /// Setter for tile scale
    /// \details
    /// Allows you to set the tile's (sprite's) scale.
    void setScale(const sf::Vector2f & newScale);

    /// \brief
    /// Getter for tile scale
    /// \details
    /// Returns the tile's (sprite's) scale.
    const sf::Vector2f& getScale() const;

    /// \brief
    /// Getter for tile size
    /// \details
    /// Returns the tile's (sprite's) size.
    const sf::Vector2f getSize() const;

    /// \brief
    /// Getter for tile bounds
    /// \details
    /// Return the tile's (sprite's) global bounds.
    const sf::FloatRect getBounds() const;

    /// \brief
    /// Draws the tile
    /// \details
    /// Draws the tile on the given window.
    void draw(sf::RenderWindow & window) const;
};

#endif // __TILE_HPP__

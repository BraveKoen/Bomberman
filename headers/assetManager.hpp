#ifndef __ASSETMANAGER_HPP__
#define __ASSETMANAGER_HPP__

#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"

/// \brief
/// AssetManager class
/// \details
/// The AssetManager class is resposible for keeping track of the variety of
/// different resources that will be loaded during the game. In its current
/// state, the AssetManager only works with textures and fonts. For each type
/// of resource, an associative array is used to store all of the items. A
/// unique key in form of a string is used to store and retrieve resources.
class AssetManager{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    /// \brief
    /// Loads a texture from disk
    /// \details
    /// Loads a texture from disk if it's not been loaded before, otherwise 
    /// returns a reference to the already loaded texture.
    const sf::Texture& loadTexture(const resourceData& resource);
    /// \brief
    /// Loads a texture from disk
    /// \details
    /// Loads a texture from disk if it's not been loaded before, otherwise 
    /// returns a reference to the already loaded texture.
    const sf::Texture& loadTexture(std::string name, std::string fileName);
    /// \brief
    /// Loads a font from disk
    /// \details
    /// Loads a font from disk if it's not been loaded before, otherwise 
    /// returns a reference to the already loaded font.
    const sf::Font& loadFont(const resourceData& resource);
    /// \brief
    /// Loads a font from disk
    /// \details
    /// Loads a font from disk if it's not been loaded before, otherwise 
    /// returns a reference to the already loaded font.
    const sf::Font& loadFont(std::string name, std::string fileName);

    /// \brief
    /// Reloads a texture from disk
    /// \details
    /// Reloads a texture from disk, even if the specified key is already used
    /// to keep track of another texture.
    const sf::Texture& reloadTexture(const resourceData& resource);
    /// \brief
    /// Reloads a texture from disk
    /// \details
    /// Reloads a texture from disk, even if the specified key is already used
    /// to keep track of another texture.
    const sf::Texture& reloadTexture(std::string name, std::string fileName);
    /// \brief
    /// Reloads a font from disk
    /// \details
    /// Reloads a font from disk, even if the specified key is already used
    /// to keep track of another font.
    const sf::Font& reloadFont(const resourceData& resource);
    /// \brief
    /// Reloads a font from disk
    /// \details
    /// Reloads a font from disk, even if the specified key is already used
    /// to keep track of another font.
    const sf::Font& reloadFont(std::string name, std::string fileName);

    /// \brief
    /// Retrieves an existing texture
    /// \details
    /// Returns the texture associated with the given key. If the key doesn't
    /// exist, an error message is displayed to the terminal.
    const sf::Texture& getTexture(const resourceData& resource) const;
    /// \brief
    /// Retrieves an existing texture
    /// \details
    /// Returns the texture associated with the given key. If the key doesn't
    /// exist, an error message is displayed to the terminal.
    const sf::Texture& getTexture(std::string name) const;
    /// \brief
    /// Retrieves an existing font
    /// \details
    /// Returns the font associated with the given key. If the key doesn't
    /// exist, an error message is displayed to the terminal.
    const sf::Font& getFont(const resourceData& resource) const;
    /// \brief
    /// Retrieves an existing font
    /// \details
    /// Returns the font associated with the given key. If the key doesn't
    /// exist, an error message is displayed to the terminal.
    const sf::Font& getFont(std::string name) const;
};

#endif // __ASSETMANAGER_HPP__

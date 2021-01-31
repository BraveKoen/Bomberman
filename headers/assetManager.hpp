#ifndef __ASSETMANAGER_HPP__
#define __ASSETMANAGER_HPP__

#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"

class AssetManager{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    const sf::Texture& loadTexture(const resourceData& resource);
    const sf::Texture& loadTexture(std::string name, std::string fileName);
    const sf::Font& loadFont(const resourceData& resource);
    const sf::Font& loadFont(std::string name, std::string fileName);

    const sf::Texture& reloadTexture(const resourceData& resource);
    const sf::Texture& reloadTexture(std::string name, std::string fileName);
    const sf::Font& reloadFont(const resourceData& resource);
    const sf::Font& reloadFont(std::string name, std::string fileName);

    const sf::Texture& getTexture(const resourceData& resource) const;
    const sf::Texture& getTexture(std::string name) const;
    const sf::Font& getFont(const resourceData& resource) const;
    const sf::Font& getFont(std::string name) const;
};

#endif // __ASSETMANAGER_HPP__

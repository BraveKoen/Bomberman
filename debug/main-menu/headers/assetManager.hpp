#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class AssetManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    auto loadTexture(std::string name, std::string fileName)
        -> sf::Texture const&;
    auto loadFont(std::string name, std::string fileName)
        -> sf::Font const&;
    auto getTexture(std::string name) const -> sf::Texture const&;
    auto getFont(std::string name) const -> sf::Font const&;
};

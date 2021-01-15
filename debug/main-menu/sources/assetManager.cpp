#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "../headers/assetManager.hpp"

auto AssetManager::loadTexture(
    std::string name,
    std::string fileName
) -> sf::Texture const& {
    sf::Texture texure;
    texure.loadFromFile(fileName);
    return textures[name] = texure;
}

auto AssetManager::loadFont(
    std::string name,
    std::string fileName
) -> sf::Font const& {
    sf::Font font;
    font.loadFromFile(fileName);
    return fonts[name] = font;
}

auto AssetManager::getTexture(
    std::string name
) const -> sf::Texture const& {
    return textures.at(name);
}

auto AssetManager::getFont(
    std::string name
) const -> sf::Font const& {
    return fonts.at(name);
}

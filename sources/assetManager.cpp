#include "../headers/assetManager.hpp"

const sf::Texture& AssetManager::loadTexture(std::string name, std::string fileName) {
    sf::Texture texure;
    texure.loadFromFile(fileName);
    return textures[name] = texure;
}

const sf::Font& AssetManager::loadFont(std::string name, std::string fileName) {
    sf::Font font;
    font.loadFromFile(fileName);
    return fonts[name] = font;
}

const sf::Texture& AssetManager::getTexture(std::string name) const {
    return textures.at(name);
}

const sf::Font& AssetManager::getFont(std::string name) const {
    return fonts.at(name);
}

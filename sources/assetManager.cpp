#include "../headers/assetManager.hpp"
#include "../headers/definitions.hpp"

const sf::Texture& AssetManager::loadTexture(const resourceData& resource) {
    return loadTexture(resource.name, resource.file);
}

const sf::Texture& AssetManager::loadTexture(std::string name, std::string fileName) {
    sf::Texture texture;
    texture.loadFromFile(fileName);
    return textures[name] = std::move(texture);
}

const sf::Font& AssetManager::loadFont(const resourceData& resource) {
    return loadFont(resource.name, resource.file);
}

const sf::Font& AssetManager::loadFont(std::string name, std::string fileName) {
    sf::Font font;
    font.loadFromFile(fileName);
    return fonts[name] = std::move(font);
}

const sf::Texture& AssetManager::getTexture(const resourceData& resource) const {
    return getTexture(resource.name);
}

const sf::Texture& AssetManager::getTexture(std::string name) const {
    const auto& iter = textures.find(name);

    if (iter == textures.end()) {
        std::cerr << "[WARNING] Unable to get texture: " << name << std::endl;
    }
    return iter->second;
}

const sf::Font& AssetManager::getFont(const resourceData& resource) const {
    return getFont(resource.name);
}

const sf::Font& AssetManager::getFont(std::string name) const {
    const auto& iter = fonts.find(name);

    if (iter == fonts.end()) {
        std::cerr << "[WARNING] Unable to get font: " << name << std::endl;
    }
    return iter->second;
}

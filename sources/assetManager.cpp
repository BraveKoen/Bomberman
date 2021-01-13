#include "../headers/assetManager.hpp"

void AssetManager::loadTexture(std::string name, std::string fileName){
    sf::Texture texure;

    if(texure.loadFromFile(fileName)){
        textures[name] = texure;
    }
}

sf::Texture & AssetManager::getTexture(std::string name){
    return textures[name];
}

void AssetManager::loadFont(std::string name, std::string fileName){
    sf::Font font;

    if(font.loadFromFile(fileName)){
        fonts[name] = font;
    }
}

sf::Font & AssetManager::getFont(std::string name){
    return fonts[name];
}
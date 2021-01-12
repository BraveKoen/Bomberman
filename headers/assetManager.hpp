#ifndef __ASSETMANAGER_HPP__
#define __ASSETMANAGER_HPP__

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager{
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    void loadTexture(std::string name, std::string fileName);
    sf::Texture & getTexture(std::string name);

    void loadFont(std::string name, std::string fileName);
    sf::Font & getFont(std::string name);
};

#endif // __ASSETMANAGER_HPP__

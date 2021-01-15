#ifndef __ASSETMANAGER_HPP__
#define __ASSETMANAGER_HPP__

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager{
    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
    public:
        const sf::Texture& loadTexture(std::string name, std::string fileName);
        const sf::Font& loadFont(std::string name, std::string fileName);

        const sf::Texture& getTexture(std::string name) const;
        const sf::Font& getFont(std::string name) const;
};

#endif // __ASSETMANAGER_HPP__

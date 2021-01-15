#ifndef __ASSETMANAGER_HPP__
#define __ASSETMANAGER_HPP__

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager{
<<<<<<< HEAD
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
public:
    const sf::Texture& loadTexture(std::string name, std::string fileName);
    const sf::Font& loadFont(std::string name, std::string fileName);

    const sf::Texture& getTexture(std::string name) const;
    const sf::Font& getFont(std::string name) const;
=======
    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
    public:
        const sf::Texture& loadTexture(std::string name, std::string fileName);
        const sf::Font& loadFont(std::string name, std::string fileName);

        const sf::Texture& getTexture(std::string name) const;
        const sf::Font& getFont(std::string name) const;
>>>>>>> 2dbf9784a104b2ccd8266da958bf7f16536056eb
};

#endif // __ASSETMANAGER_HPP__

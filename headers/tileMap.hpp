#ifndef __TILEMAP_HPP__
#define __TILEMAP_HPP__

#include <vector>

class TileMap{
    private:
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2u mapSize;
        std::vector<std::vector<std::string>> map;
    public:
        TileMap(sf::Vector2f position, sf::Vector2f size, sf::Vector2u mapSize=sf::Vector2u(15,15));
        TileMap(sf::Vector2f position, sf::Vector2f size, std::vector<std::vector<std::string>> map, sf::Vector2u mapSize=sf::Vector2u(15,15));
        //General setters
        void setPosition(sf::Vector2f newPosition);
        void setSize(sf::Vector2f newSize);
        void setMapSize(sf::Vector2u newMapSize);
        void setMap(std::vector<std::vector<std::string>> map);
        //Generals getters
        sf::Vector2f newPosition getPosition()const;
        sf::Vector2f newSize getSize()const;
        sf::Vector2u newMapSize getMapSize()const;
        std::vector<std::vector<std::string>> map setMap()const;
        //Tile setters and getters
        void setTile(sf::Vector2u tilePosition, std::string type); //Based on tile coordinates
        void setTile(sf::Vector2f screenPosition, std::string type); //Based on screen coordinates
        std::string getTile(sf::Vector2u tilePosition)const; //Based on tile coordinates
        std::string getTile(sf::Vector2f screenPosition)const; //Based on screen coordinates
        
        void draw(sf::RenderWindow window);
};

#endif // __TILEMAP_HPP__

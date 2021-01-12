#ifndef __BREAKABLEWALL_HPP__
#define __BREAKABLEWALL_HPP__

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

class breakableWall
{
public:
    breakableWall(GameData data);

    void spawnWall();
    void drawWall();

    const std::vector<sf::Sprite> &getSprites() const;
    void setSprites(std::vector<sf::Sprite> & sprites);

    void setWallScale(sf::Vector2f scale);

private:
    GameData gameData;
    std::vector<sf::Sprite> breakableWallSprites;
};

#endif // __BREAKABLEWALL_HPP__
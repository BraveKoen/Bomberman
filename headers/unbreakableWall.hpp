#ifndef __UNBREAKABLEWALL_HPP__
#define __UNBREAKABLEWALL_HPP__

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

class unbreakableWall
{
public:
    unbreakableWall(GameData data);

    void spawnWall();
    void drawWall();

    const std::vector<sf::Sprite> &getSprites() const;
    void setSprites(std::vector<sf::Sprite> & sprites);

    void setWallScale(sf::Vector2f scale);

private:
    GameData gameData;
    std::vector<sf::Sprite> unbreakableWallSprites;
};

#endif // __UNBREAKABLEWALL_HPP__

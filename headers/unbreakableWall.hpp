#ifndef __UNBREAKABLEWALL_HPP__
#define __UNBREAKABLEWALL_HPP__

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

class UnbreakableWall
{
public:
    UnbreakableWall(gameDataRef data);

    void spawnWall(sf::Vector2f position);
    void drawWall();

    const std::vector<sf::Sprite> &getSprites() const;
    void setSprites(std::vector<sf::Sprite> & sprites);

    void setWallScale(sf::Vector2f scale);

private:
    gameDataRef gameData;
    std::vector<sf::Sprite> unbreakableWallSprites;
};

#endif // __UNBREAKABLEWALL_HPP__

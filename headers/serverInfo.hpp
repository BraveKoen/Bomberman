#ifndef __SEVERINFO_HPP__
#define __SEVERINFO_HPP__
#include <SFML\Graphics.hpp>

struct PlayerInfo{
    int      playerId;
    sf::Vector2f pos;
    bool disconnected;
    sf::Vector2f aimDir;
    bool spawnedBullet;
};

struct LobbyInfo{
    int      playerId;
    bool disconnected;
    int newPlayer;
};

#endif // __SEVERINFO_HPP__

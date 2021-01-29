#ifndef __SEVERINFO_HPP__
#define __SEVERINFO_HPP__
#include <SFML\Graphics.hpp>
#include <iostream>
#include "tileMap.hpp"

struct PlayerInfo{
    int      playerId;
    sf::Vector2f pos;
    bool disconnected;
    bool spawnedBomb;
    int playerHealth;
};

struct LobbyInfo{
    int playerId = -1;
    int opponentsCount = 0;
    bool disconnected = false;
    bool ready = false;
    std::string map;
};

#endif // __SEVERINFO_HPP__

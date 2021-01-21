#ifndef __SEVERINFO_HPP__
#define __SEVERINFO_HPP__
#include <SFML\Graphics.hpp>

struct PlayerInfo{
    int      playerId;
    sf::Vector2f pos;
    bool disconnected;
    bool spawnedBomb;
};

struct LobbyInfo{
    int      playerId = -1;
    bool disconnected = false;
    int newPlayer;
    bool ready = false;
};

#endif // __SEVERINFO_HPP__

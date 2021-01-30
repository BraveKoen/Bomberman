#ifndef __SEVERINFO_HPP__
#define __SEVERINFO_HPP__
#include <SFML\Graphics.hpp>
#include <iostream>
#include "tileMap.hpp"

/// \brief
///  struct PlayerInfo
/// \details
/// playerId so the client nows who to update
/// pos where to place the opponent
/// disconnected when a player quits the game
/// spawnedBomb to send when the opponent placed a bomb
/// playeHealth how many lives every opponents has
struct PlayerInfo{
    int      playerId;
    sf::Vector2f pos;
    bool disconnected;
    bool spawnedBomb;
    int playerHealth;
};

/// \brief
///  struct LobbyInfo
/// \details
/// player is -1 for the server to understand that he has to send a new playerId
/// opponentsCount for how many players they have to spawn
/// disconnected when the player closes the game
/// ready is for the host to start the game
/// player will receive the map from the host so they all play on the same map
struct LobbyInfo{
    int playerId = -1;
    int opponentsCount = 0;
    bool disconnected = false;
    bool ready = false;
    std::string map;
};

#endif // __SEVERINFO_HPP__

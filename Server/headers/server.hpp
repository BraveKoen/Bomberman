#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <iostream>

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

class Server{
private:
    sf::UdpSocket socket;
    std::map<sf::IpAddress ,std::vector<int>> playermap;
    int playerCount = 1;
    bool playersReady = 0;
    uint16_t port;
    sf::IpAddress ip;
    

public:
    Server(sf::IpAddress ip, uint16_t port);

    /// \brief
    ///  void run
    /// \details
    /// will call lobby function
    void run();

    /// \brief
    ///  void serverReceiveInGame
    /// \details
    /// this function will handle all the packets that is from the struct PlayerInfo
    /// and will call serverSend 
    void serverReceiveInGame();

    /// \brief
    ///  void seversend sf::Packet sf::IpAdress int
    /// \details
    /// send the given packet to the given ip and port
    /// it will loop through all the players in the list
    void serverSend(sf::Packet &packet , sf::IpAddress ip, int port);

    /// \brief
    ///  void lobby
    /// \details
    /// handles all the playercount and gives new player a id
    void lobby();

    /// \brief
    ///  void serverBroadcast
    /// \details
    /// send the packet to all players
    void serverBroadcast(sf::Packet &packet);

};

#endif // __SERVER_HPP__

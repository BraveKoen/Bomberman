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
    //sf::RenderWindow window;
    sf::UdpSocket socket;
    //std::map<uint16_t, sf::IpAddress> players;
    //std::map<int, uint16_t> playerId;
    std::map<sf::IpAddress ,std::vector<int>> playermap;
    int playerCount = 1;
    bool playersReady = 0;
    uint16_t port;
    sf::IpAddress ip;
    

public:
    Server(sf::IpAddress ip, uint16_t port);

    void run();
    void serverReceiveInGame();
    void serverSend(sf::Packet &packet , sf::IpAddress ip, int port);
    void lobby();
    void serverBroadcast(sf::Packet &packet);

};

#endif // __SERVER_HPP__

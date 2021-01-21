#ifndef __CONNECT_HPP__
#define __CONNECT_HPP__

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "serverInfo.hpp"


class Server{
private:
    int playerNumber = -1;
    sf::IpAddress server;
    unsigned short port;
    sf::UdpSocket socket;
    sf::Packet sendPacket;
    bool connection = false;
    LobbyInfo lobby;
    std::thread mThread;

public:
    Server(sf::IpAddress ip, unsigned short port);

    void testConnection(int playerNumber, sf::IpAddress ip, unsigned short port);
    
    void run();

    void sendData(PlayerInfo &playerInfo);

    void sendData(LobbyInfo &lobbyInfo);

    void serverGetPlayerId(int playerId);
    int getPlayerId(int playerId);

    void playerDisconnect();
    PlayerInfo receiveData();

    int getPlayerId();

    void playerReady();

};

#endif // __CONNECT_HPP__
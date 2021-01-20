#ifndef __CONNECT_HPP__
#define __CONNECT_HPP__

#include <SFML/Network.hpp>
#include <iostream>

#include "../sources/struct.cpp"



class Server{
private:
    int playerNumber = -1;
    sf::IpAddress server;
    unsigned short port;
    sf::UdpSocket socket;
    sf::Packet sendPacket;
    bool connection = false;

public:
    Server(int playerNumber, sf::IpAddress ip, unsigned short port);

    void testConnection(int playerNumber, sf::IpAddress ip, unsigned short port);
    void run();

    void sendData(PlayerInfo &playerInfo);

    void sendData(LobbyInfo &lobbyInfo);
    PlayerInfo receiveData();
};

#endif // __CONNECT_HPP__
#ifndef __CONNECT_HPP__
#define __CONNECT_HPP__

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "serverInfo.hpp"


class Server{
private:
    int playerNumber;
    int opponentCount = 0;
    sf::IpAddress server;
    unsigned short port;
    sf::UdpSocket socket;
    sf::Packet sendPacket;
    bool connection = false;
    bool goToMapSelect = false;
    LobbyInfo lobby;
    std::thread mThread;
    std::vector<std::vector<std::string>> map;
    
    std::string mapEncoder(std::vector<std::vector<std::string>> map);
    std::vector<std::vector<std::string>> mapDecoder(std::string str);

public:
    Server(sf::IpAddress ip, unsigned short port);

    void testConnection(int playerNumber, sf::IpAddress ip, unsigned short port);
    
    void run();

    void sendData(PlayerInfo &playerInfo);

    void sendData(LobbyInfo &lobbyInfo);

    void serverGetPlayerId(int playerId);

    void playerDisconnect();
    PlayerInfo receiveDataInGame();
    bool receiveDataLobby(bool stopIfHost=true);

    int getPlayerId();

    int getOpponentCount();

    void playerReady();

    void hostReady(std::vector<std::vector<std::string>> map);

    std::vector<std::vector<std::string>> getMap(){return map;}

    bool getGoToMapSelect(){return goToMapSelect;}
};

#endif // __CONNECT_HPP__
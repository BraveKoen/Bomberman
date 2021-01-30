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
    /// \brief
    /// Server ip for connection with port
    /// \details
    ///
    Server(sf::IpAddress ip, unsigned short port);

    /// \brief
    /// void sendData playerInfo 
    /// \details
    /// sends a struct to the server
    void sendData(PlayerInfo &playerInfo);

    /// \brief
    /// void send lobbyInfo
    /// \details
    /// send LobbyData to the server
    void sendData(LobbyInfo &lobbyInfo);

    /// \brief
    /// void serverGetPLayerId
    /// \details
    /// sends a request that you need a playerId
    void serverGetPlayerId(int playerId);

    /// \brief
    /// void PLayerDisconnect
    /// \details
    /// when a player leaves the program or the game this will send a message to te server that the player is leaves
    void playerDisconnect();

    /// \brief
    /// playerInfo receiveDataInGame
    /// \details
    /// will return a playerInfo if it receive a data packets 
    /// When it receives nothing is will wait!
    PlayerInfo receiveDataInGame();

    /// \brief
    /// bool receiveDataLobby stopifhost
    /// \details
    /// return true when the games starts or when you receive playerId 1
    /// when the bool is false it will not return true when playerId 1 receives
    bool receiveDataLobby(bool stopIfHost=true);

     /// \brief
    /// int getPlayerId
    /// \details
    /// return playerId from server
    int getPlayerId();

    /// \brief
    /// void setPlayerId int newPLayerId
    /// \details
    /// with this function you can reset the playerId
    void setPlayerId(int newPlayerId);

    /// \brief
    /// void getOpponentCount
    /// \details
    /// returns a int with how many opponents you play against
    int getOpponentCount();

    /// \brief
    /// void playerReady!
    /// \details
    /// sends a message to the server when a user says he is ready
    void playerReady();

    /// \brief
    ///  void hostReady  std::vector<std::vector<std::string>>
    /// \details
    /// sends the hole map through and will start the game
    void hostReady(std::vector<std::vector<std::string>> map);

    /// \brief
    ///  std::vector<std::vector<std::string>> map
    /// \details
    /// returns a falid map
    std::vector<std::vector<std::string>> getMap(){return map;}

    bool getGoToMapSelect(){return goToMapSelect;}
};

#endif // __CONNECT_HPP__
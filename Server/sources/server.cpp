#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include "../headers/server.hpp"

sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& m){

    return packet << m.playerId << m.pos.x << m.pos.y << m.disconnected << m.spawnedBomb << m.playerHealth;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& m){

    return packet >> m.playerId >> m.pos.x >> m.pos.y >> m.disconnected >> m.spawnedBomb >> m.playerHealth;
}

sf::Packet& operator <<(sf::Packet& packet, const LobbyInfo& m){

    return packet << m.playerId << m.opponentsCount << m.disconnected << m.ready << m.map;
}
sf::Packet& operator >>(sf::Packet& packet, LobbyInfo& m){

    return packet >> m.playerId >> m.opponentsCount >> m.disconnected >> m.ready >> m.map;
}

Server::Server(sf::IpAddress ip, uint16_t port):
    port(port),
    ip(ip)
{
    socket.bind(port, ip);
}

void Server::run(){
    lobby();
}


void Server::lobby(){
    std::cout << "Started lobby" << std::endl;
    LobbyInfo lobbyInfo;
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    while(true){
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> lobbyInfo;
            if(lobbyInfo.playerId == -1){
                std::cout << "unknown" << std::endl;
                std::cout << portOntvanger << std::endl;
                lobbyInfo.playerId = playerCount;
                lobbyInfo.ready = false;
                packetOntvanger.clear();
                packetOntvanger << lobbyInfo;
                socket.send(packetOntvanger, ipOntvanger, portOntvanger);
            }else{
                if(playermap.find(ipOntvanger) == playermap.end()){
                    if(lobbyInfo.disconnected == true){
                        std::cout << "lol" << std::endl;
                    }else{
                        playermap[ipOntvanger] = {lobbyInfo.playerId, portOntvanger};
                        lobbyInfo.ready = false;
                        lobbyInfo.playerId = playerCount;
                        playerCount++;
                        packetOntvanger.clear();
                        packetOntvanger << lobbyInfo;
                        std::cout << "New player" << " Ip: " << ipOntvanger << " Port: " << portOntvanger << " playerid: "<< lobbyInfo.playerId << std::endl;
                        serverBroadcast(packetOntvanger);
                    }
                    
                    
                }else if(lobbyInfo.disconnected == true){
                    std::cout << " Ip: " << ipOntvanger << " disconnected! lobby" << std::endl;
                    playermap.erase(ipOntvanger);
                }else if(lobbyInfo.ready && (lobbyInfo.playerId == 1)){
                    packetOntvanger.clear();
                    lobbyInfo.ready = true;
                    lobbyInfo.opponentsCount = playermap.size();//-1 omdat je altijd 1 player hebt
                    packetOntvanger << lobbyInfo;
                    std::cout << " host started the game with " << playermap.size() -1 << " opponents!" << std::endl;
                    serverBroadcast(packetOntvanger); 
                    serverReceiveInGame();
                }else{
                    std::cout << "Player already connected!" << std::endl;
                    std::cout << "player" << " Ip: " << ipOntvanger << " Port: " << portOntvanger << " playerid: "<< lobbyInfo.playerId << std::endl;
                }
            }
        }
    }
}


void Server::serverReceiveInGame(){
    PlayerInfo playerInfo;
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    while(true){
        packetOntvanger.clear();
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> playerInfo;
            if(playermap.find(ipOntvanger) != playermap.end()){ // staat dus in de lijst
                if(playerInfo.disconnected == true){
                    std::cout << "disconnected! player: " << playerInfo.playerId << std::endl;
                    playermap.erase(ipOntvanger);
                }
            serverSend(packetOntvanger, ipOntvanger, portOntvanger);
            }       
        }
    }
}

void Server::serverSend(sf::Packet &packet , sf::IpAddress ip, int port){
    for(auto& value : playermap){
        //socket.send(packet, value.first, value.second[1]);
      //  std::cout << value.second << "  " << ip  << std::endl;
        //std::cout << "---" << std::endl;
        if(value.second[1] != port){
            socket.send(packet, value.first, value.second[1]);
        }
    }
}
void Server::serverBroadcast(sf::Packet &packet){
    LobbyInfo lobbyInfo;
    packet >> lobbyInfo;
    lobbyInfo.opponentsCount = playermap.size() - 1;
    packet.clear();
    packet << lobbyInfo;
    for(auto& value : playermap){
        //packet.clear();
        socket.send(packet, value.first, value.second[1]);
    }
}
#include "../headers/server.hpp"
#include "../headers/opponent.hpp"


sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& m){

    return packet << m.playerId << m.pos.x << m.pos.y << m.disconnected << m.spawnedBomb;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& m){

    return packet >> m.playerId >> m.pos.x >> m.pos.y >> m.disconnected >> m.spawnedBomb;
}

sf::Packet& operator <<(sf::Packet& packet, const LobbyInfo& m){

    return packet << m.playerId << m.disconnected << m.newPlayer << m.ready;
}
sf::Packet& operator >>(sf::Packet& packet, LobbyInfo& m){

    return packet >> m.playerId >> m.disconnected >> m.newPlayer >> m.ready;
}



Server::Server(sf::IpAddress ip, unsigned short port):
    playerNumber{playerNumber},
    server{ip},
    port{port}
{
    socket.bind(socket.getLocalPort(), sf::IpAddress::getLocalAddress());
    std::cout << "Local port: " << socket.getLocalPort() << std::endl;
    
}


void Server::serverGetPlayerId(int playerId){
    lobby.playerId = playerId;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
}

int Server::getPlayerId(int playerId){
    lobby.playerId = playerId;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
}


void Server::sendData(PlayerInfo &playerInfo){
    socket.setBlocking(false);
    sendPacket.clear();
    
    sendPacket << playerInfo;
    socket.send(sendPacket, server, port);
    socket.setBlocking(true);
}

void Server::sendData(LobbyInfo &lobbyInfo){
    std::cout << "send data!" << std::endl;
    socket.setBlocking(false);
    sendPacket.clear();
    
    sendPacket << lobbyInfo;
    socket.send(sendPacket, server, port);
    socket.setBlocking(true);
}


PlayerInfo Server::receiveData(){ 
    LobbyInfo lobbyInfo;
    while(true){
        PlayerInfo playerInfo;
        sf::Packet packetOntvanger;
        sf::IpAddress ipOntvanger;
        uint16_t portOntvanger;
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> lobbyInfo;
            playerNumber = lobbyInfo.playerId;
            return playerInfo;
        }
    }
}

void Server::run(){
    LobbyInfo lobbyInfo;
    PlayerInfo playerInfo;
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    while(true){
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> lobbyInfo;
            playerNumber = lobbyInfo.playerId;
            std::cout << "PlayerId: " <<  lobbyInfo.playerId << std::endl;
            //std::cout << "PlayerId: " << playerInfo.playerId << " X: " << playerInfo.pos.x << " Y: " << playerInfo.pos.y <<  std::endl;
        }
    }
}

void Server::playerDisconnect(){
    PlayerInfo playerInfo;
    lobby.disconnected = true;
    playerInfo.disconnected = true;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
    sendPacket.clear();
    sendPacket << playerInfo;
    socket.send(sendPacket, server, port);
}

int Server::getPlayerId(){
    return playerNumber;
}

void Server::playerReady(){
    lobby.ready = true;
    lobby.disconnected = true;
    playerInfo.disconnected = true;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
    sendPacket.clear();
    sendPacket << playerInfo;
    socket.send(sendPacket, server, port);
}

int Server::getPlayerId(){
    return playerNumber;
}

void Server::playerReady(){
    lobby.ready = true;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
}
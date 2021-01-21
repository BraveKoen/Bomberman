#include "../headers/server.hpp"


sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& m){

    return packet << m.playerId << m.pos.x << m.pos.y << m.disconnected << m.aimDir.x << m.aimDir.y << m.spawnedBullet;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& m){

    return packet >> m.playerId >> m.pos.x >> m.pos.y >> m.disconnected >> m.aimDir.x >> m.aimDir.y >> m.spawnedBullet;
}

sf::Packet& operator <<(sf::Packet& packet, const LobbyInfo& m){

    return packet << m.playerId << m.disconnected << m.newPlayer;
}
sf::Packet& operator >>(sf::Packet& packet, LobbyInfo& m){

    return packet >> m.playerId >> m.disconnected >> m.newPlayer;
}



Server::Server(sf::IpAddress ip, unsigned short port):
    playerNumber{playerNumber},
    server{ip},
    port{port}
{
    socket.bind(socket.getLocalPort(), sf::IpAddress::getLocalAddress());
    std::cout << "Local port: " << socket.getLocalPort() << std::endl;
    
}


int Server::getPlayerId(int playerId){
    lobby.playerId = playerId;
    lobby.disconnected = false;
    lobby.newPlayer = 3;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
        packetOntvanger >> lobby;
        std::cout << lobby.playerId << std::endl;
        return lobby.playerId;
    }
    return -1;
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
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) != sf::Socket::Done){
            packetOntvanger >> lobbyInfo;
            std::cout << "Ip: " << ipOntvanger << " port: " << portOntvanger << lobbyInfo.playerId << std::endl;
            return playerInfo;
        }
    }
}

void Server::run(){
    PlayerInfo playerInfo;
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    while(true){
        std::cout << "hier1" << std::endl;
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            //packetOntvanger >> playerInfo;
            std::cout << "Ip: " << ipOntvanger << " port: " << portOntvanger <<  std::endl;
            //std::cout << "PlayerId: " << playerInfo.playerId << " X: " << playerInfo.pos.x << " Y: " << playerInfo.pos.y <<  std::endl;
        }
        std::cout << "hier2" << std::endl;
    }
}

void Server::playerDisconnect(){
    lobby.disconnected = true;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
}
#include "../headers/server.hpp"
#include "../headers/opponent.hpp"


sf::Packet& operator <<(sf::Packet& packet, const PlayerInfo& m){

    return packet << m.playerId << m.pos.x << m.pos.y << m.disconnected << m.spawnedBomb;
}
sf::Packet& operator >>(sf::Packet& packet, PlayerInfo& m){

    return packet >> m.playerId >> m.pos.x >> m.pos.y >> m.disconnected >> m.spawnedBomb;
}

sf::Packet& operator <<(sf::Packet& packet, const LobbyInfo& m){

    return packet << m.playerId << m.opponentsCount << m.disconnected << m.ready << m.map;
}
sf::Packet& operator >>(sf::Packet& packet, LobbyInfo& m){

    return packet >> m.playerId >> m.opponentsCount >> m.disconnected >> m.ready >> m.map;
}



Server::Server(sf::IpAddress ip, unsigned short port):
    server{ip},
    port{port}
{
    socket.bind(socket.getLocalPort(), sf::IpAddress::getLocalAddress());
    std::cout << "Local port: " << socket.getLocalPort() << std::endl;
    playerNumber = -1;
    
}


void Server::serverGetPlayerId(int playerId){
    std::cout << "server: " << server << " port: " << port<< std::endl;
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


PlayerInfo Server::receiveDataInGame(){ 
    PlayerInfo playerInfo;
    while(true){
        sf::Packet packetOntvanger;
        sf::IpAddress ipOntvanger;
        uint16_t portOntvanger;
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> playerInfo;
            return playerInfo;
        }
    }
}
bool Server::receiveDataLobby(){ 
    LobbyInfo lobbyInfo;
    while(true){
        sf::Packet packetOntvanger;
        sf::IpAddress ipOntvanger;
        uint16_t portOntvanger;
        if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
            packetOntvanger >> lobbyInfo;
            std::cout << "ready: " << lobbyInfo.ready << std::endl;
            std::cout << "playerId: " << lobbyInfo.playerId << std::endl;
            opponentCount = lobbyInfo.opponentsCount;
            if(playerNumber == -1){
                playerNumber = lobbyInfo.playerId;
                std::cout << "playerId ontvangen: " << lobbyInfo.playerId << std::endl;
                serverGetPlayerId(lobbyInfo.playerId);
                if(playerNumber == 1){
                    std::cout << "player 1 gaat naar lobby" << std::endl;
                    return true;
                }            
            }
            if(lobbyInfo.ready){
                map = mapDecoder(lobbyInfo.map);
                return true;
            }
        }   
    }
    return false;
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
    std::cout << "send disconnect" << std::endl;
    PlayerInfo playerInfo;
    playerInfo.playerId = playerNumber;
    playerInfo.disconnected = true;
    sendPacket.clear();
    sendPacket << playerInfo;
    socket.send(sendPacket, server, port);

    //sendPacket << playerInfo;
   // socket.send(sendPacket, server, port);
}

int Server::getPlayerId(){
    return playerNumber;
}

int Server::getOpponentCount(){
    return opponentCount;
}

void Server::playerReady(){
    std::cout << "server: " << server << " port: " << port<< std::endl;
    lobby.ready = false;
    lobby.playerId = playerNumber;
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
    sf::Time transitionTime = sf::seconds(0.5f);
    sf::sleep(transitionTime);
}

void Server::hostReady(std::vector<std::vector<std::string>> map){
    sf::Packet packetOntvanger;
    sf::IpAddress ipOntvanger;
    uint16_t portOntvanger;
    lobby.disconnected = false;
    lobby.ready = true;
    lobby.playerId = playerNumber;
    lobby.map = mapEncoder(map);
    sendPacket.clear();
    sendPacket << lobby;
    socket.send(sendPacket, server, port);
    if(socket.receive(packetOntvanger, ipOntvanger, portOntvanger) == sf::Socket::Done){
        packetOntvanger >> lobby;
        opponentCount = lobby.opponentsCount;
        std::cout << "players: " << opponentCount << std::endl;
    }
    
}

std::vector<std::vector<std::string>> Server::mapDecoder(std::string str){
    std::cout << str << std::endl;
    std::vector<std::vector<std::string>> temp;
    int count = 0;
    std::string word = "";
    std::vector<std::string> mapLine = {};
    for (auto x : str){
        if (x == ' '){
            std::string srr = word;
            srr.erase(remove(srr.begin(), srr.end(), ' '), srr.end()); 
            mapLine.push_back(srr);
            //std::cout << word;
            word = "";
        }
        if(x == ';'){
            count++;
            temp.push_back(mapLine);
            mapLine = {};
            //std::cout << std::endl;
            word = "";

        }
        else{
            word = word + x;
        }
        
    }
    temp.push_back(mapLine);
    temp.erase(temp.begin());
    return temp;
}

std::string Server::mapEncoder(std::vector<std::vector<std::string>> map){
    std::string mapje;
    for(auto i : map){
        mapje += ';';
        for(auto j : i){
            mapje += j;
            mapje += ' ';
            
        }
    }
    return mapje;
}
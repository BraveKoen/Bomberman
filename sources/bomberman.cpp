#include <iostream>
#include <thread>
#include <mutex>
#include "../headers/game.hpp"
#include "../headers/definitions.hpp"
#include "../headers/server.hpp"

void receve(){
    std::cout << "Hello" << std::endl;
    
}


int main(){
    //LobbyInfo lob;
    //lob.playerId = 34;
    //Server server{-1, "192.168.2.14", 1999};
    //server.sendData(lob);
    //server.receiveData();
    
    Game(Resource::screenWidth, Resource::screenHeight, "Bomberman");
}

#include <iostream>
#include <SFML/Network.hpp>
#include "../headers/server.hpp"


int main(int argc, const char** argv) {
    //sf::IpAddress kaas = "77.161.253.51";
    sf::IpAddress kaas = sf::IpAddress::getLocalAddress();
    std::cout << kaas << std::endl;
    std::cout << sf::IpAddress::getLocalAddress() << std::endl;
    Server server{kaas, 1999};
    server.lobby();
	return 0;
}
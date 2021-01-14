#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/inGameState.hpp"


InGameState::InGameState(gameDataRef data):
    data(data)
{
}

void InGameState::init(){
    data->assetManager.loadTexture("Player", "resources/man.gif");
    data->assetManager.loadTexture("Dynamite", "resources/dynamite.png");
    
    bHandler = std::make_shared<BombHandler>(data);
    players.push_back(std::make_unique<Player>(data, bHandler, 0));
    
    bool lol = 0;
    for(int i; i <= data->playerCount; i ++){
        players.push_back(std::make_unique<Player>(data, bHandler, lol));
        lol = true;
    }
}

void InGameState::handleInput(){
        sf::Event event;

    while (data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            data->window.close();
        }
    }
    
}

void InGameState::update(float delta) {

    for(auto &player : players){
        player->playerMove();
    }

    
    return;
    
}

void InGameState::draw(float delta) {
    
    data->window.clear(sf::Color::Blue);

    for(auto &player : players){
            player->draw();
        }

    bHandler->update();
    bHandler->draw();
    data->window.display();
}

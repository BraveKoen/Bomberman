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
    p1 = std::make_unique<Player>(data, bHandler);
}

void InGameState::handleInput(){
        sf::Event event;

    while (data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            data->window.close();
        } else if (sf::Event::KeyPressed == event.type) {
            p1->playerMove(event.key.code);
        }
    }
    
}

void InGameState::update(float delta) {
    
    return;
    
}

void InGameState::draw(float delta) {
    
    data->window.clear(sf::Color::Blue);
    p1->draw();
    bHandler->update();
    bHandler->draw();
    data->window.display();
}

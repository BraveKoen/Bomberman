#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/inGameState.hpp"


InGameState::InGameState(gameDataRef data):
    data(data)
{
}

void InGameState::init(){
    data->assetManager.loadTexture("Player", "resources/button-1.png");
    p1 = new Player(data);
    
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
    data->window.display();
}

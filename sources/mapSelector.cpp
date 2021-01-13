#include <iostream>
#include "../headers/mapSelector.hpp"
#include "../headers/definitions.hpp"

MapSelector::MapSelector(gameDataRef gameData):
gameData(gameData)
{}

void MapSelector::init(){
    gameData->assets.loadTexture("mapSelector background", mapSelectorBackgroundFilepath);
    gameData->assets.loadTexture("mapSelector option", mapSelectorOptionFilepath);
    background.setTexture(gameData->assets.getTexture("mapSelector background"));
    //hier iets in de menuOptions zetten
    for(unsigned short int i=0; i<menuOptions.size(); i++){
        menuOptions[i].setTexture(gameData->assets.getTexture("mapSelector option"));
        menuOptions[i].setPosition((screenWidth/2) - (_title.getGlobalBounds().width/2), ((screenHeight/2) - (_title.getGlobalBounds().height/2) + (i*10)));
    }
    
}

void mapSelector::handleInput(){
    sf::Event event

    while(gameData->window.pollEvent(event)){
        if( event.type == sf::Event::Closed ){
            gameData->window.close();
        }
        for(unsigned short int i=0; i<menuOptions.size(); i++){
            if(gameData->input.isSpriteClicked(menuOptions[i], sf::Mouse::Left, gameData)){
                std::cout << "This should now select a map" << std::endl;
            }            
        }
    }
}

void mapSelector::update(float deltaTime){

}

void mapSelector::draw(float deltaTime){
    gameData->window.clear();

    gameData->window.draw(background);
    gameData->option.draw(background);

    gameData->window.display();
}
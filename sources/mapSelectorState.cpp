#include <iostream>
#include "../headers/mapSelectorState.hpp"
#include "../headers/definitions.hpp"
#include <experimental/filesystem>
#include <string>

MapSelectorState::MapSelectorState(gameDataRef gameData):
    gameData(gameData)
{}

void MapSelectorState::init(){

    for(const auto & entry : std::experimental::filesystem::directory_iterator(mapFolderLocation)){
        std::cout << entry.path() << std::endl; 
    }
        
    gameData->assetManager.loadTexture("mapSelectorState background", mapSelectorStateBackgroundFilepath);
    gameData->assetManager.loadTexture("mapSelectorState option", mapSelectorStateOptionFilepath);
    background.setTexture(gameData->assetManager.getTexture("mapSelectorState background"));
    sf::Vector2f mapSelectorStateBackgroundSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("mapSelectorState background").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("mapSelectorState background").getSize().y )
	);
    background.setScale(
                        gameData->window.getSize().x/mapSelectorStateBackgroundSize.x, 
                        gameData->window.getSize().y/mapSelectorStateBackgroundSize.y
    );
    
    
    //hier iets in de ammountOfMaps zetten
    int ammountOfMaps = 5;
    sf::Vector2f mapSelectorStateOptionSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("mapSelectorState option").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("mapSelectorState option").getSize().y )
	);
    for(unsigned int i=0; i<ammountOfMaps; i++){
        sf::Sprite optionSprite;
        optionSprite.setTexture(gameData->assetManager.getTexture("mapSelectorState option"));
        optionSprite.setScale(
            (gameData->window.getSize().x/mapSelectorStateOptionSize.x)/5, 
            (gameData->window.getSize().y/mapSelectorStateOptionSize.y)/10
        );
        optionSprite.setPosition(
            (gameData->window.getSize().x/20), 
            ((gameData->window.getSize().y/10) - (optionSprite.getGlobalBounds().height/5) 
                + (i*((gameData->window.getSize().y/5) - (optionSprite.getGlobalBounds().height/5))))
        );
        menuOptions.push_back(optionSprite);

        sf::Text optionText;
        optionText.setFont(gameData->assetManager.getFont("default font"));
        //add filename here pls okay thanks
        optionText.setString("filename");
        optionText.setFillColor(sf::Color::Cyan);
        optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
        optionText.setPosition(
            (optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), 
            (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/3.4)
        );
        menuOptionsText.push_back(optionText);
    }
    
}


void MapSelectorState::handleInput(){
    sf::Event event;

    while(gameData->window.pollEvent(event)){
        if( event.type == sf::Event::Closed ){
            gameData->window.close();
        }
        for(unsigned short int i=0; i<menuOptions.size(); i++){
            if(gameData->inputManager.isSpriteClicked(menuOptions[i], sf::Mouse::Left, gameData->window)){
                std::cout << "This should now select a map" << std::endl;
            }            
        }
    }
}

void MapSelectorState::update(float deltaTime){

}

void MapSelectorState::draw(float deltaTime){
    gameData->window.clear();

    gameData->window.draw(background);
    for(unsigned short int i=0; i<menuOptions.size(); i++){
        gameData->window.draw(menuOptions[i]);
        gameData->window.draw(menuOptionsText[i]);
    }
    

    gameData->window.display();
}
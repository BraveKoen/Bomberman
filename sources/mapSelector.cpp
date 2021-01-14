#include <iostream>
#include "../headers/mapSelector.hpp"
#include "../headers/definitions.hpp"
#include <experimental/filesystem>
#include <string>

MapSelector::MapSelector(gameDataRef gameData):
gameData(gameData)
{}

void MapSelector::init(){

    for(const auto & entry : std::experimental::filesystem::directory_iterator(mapFolderLocation)){
        std::cout << entry.path() << std::endl; 
    }
        
    gameData->assetManager.loadTexture("mapSelector background", mapSelectorBackgroundFilepath);
    gameData->assetManager.loadTexture("mapSelector option", mapSelectorOptionFilepath);
    background.setTexture(gameData->assetManager.getTexture("mapSelector background"));
    sf::Vector2f mapSelectorBackgroundSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("mapSelector background").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("mapSelector background").getSize().y )
	);
    background.setScale(gameData->window.getSize().x/mapSelectorBackgroundSize.x, gameData->window.getSize().y/mapSelectorBackgroundSize.y);
    
    
    //hier iets in de ammountOfMaps zetten
    int ammountOfMaps = 5;
    sf::Vector2f mapSelectorOptionSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("mapSelector option").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("mapSelector option").getSize().y )
	);
    for(unsigned int i=0; i<ammountOfMaps; i++){
        sf::Sprite optionSprite;
        optionSprite.setTexture(gameData->assetManager.getTexture("mapSelector option"));
        optionSprite.setScale((gameData->window.getSize().x/mapSelectorOptionSize.x)/5, (gameData->window.getSize().y/mapSelectorOptionSize.y)/10);
        optionSprite.setPosition((gameData->window.getSize().x/20), ((gameData->window.getSize().y/10)- (optionSprite.getGlobalBounds().height/5) + (i*((gameData->window.getSize().y/5) - (optionSprite.getGlobalBounds().height/5)))));
        menuOptions.push_back(optionSprite);

        sf::Text optionText;
        optionText.setFont(gameData->assetManager.getFont("default font"));
        //add filename here pls okay thanks
        optionText.setString("filename");
        optionText.setFillColor(sf::Color::Cyan);
        optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
        optionText.setPosition((optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/3.4)/*-optionText.getGlobalBounds().height/1.3*/);
        menuOptionsText.push_back(optionText);
    }
    
}


void MapSelector::handleInput(){
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

void MapSelector::update(float deltaTime){

}

void MapSelector::draw(float deltaTime){
    gameData->window.clear();

    gameData->window.draw(background);
    for(unsigned short int i=0; i<menuOptions.size(); i++){
        gameData->window.draw(menuOptions[i]);
        gameData->window.draw(menuOptionsText[i]);
    }
    

    gameData->window.display();
}
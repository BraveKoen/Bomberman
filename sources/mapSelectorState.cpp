#include "../headers/mapSelectorState.hpp"
#include "../headers/definitions.hpp"
#include <experimental/filesystem>
#include <stdio.h>
#include <iostream>
#include <fstream>

bool MapSelectorState::isValidFile(std::string fileName){
    bool valid = true;
    std::ifstream file(fileName);
    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string word; 
        while (ss >> word){
            if(
                word != "solid" &&
                word != "break" &&
                word != "empty" &&
                word != "play1" &&
                word != "play2" &&
                word != "play3" &&
                word != "play4"
            ){
                valid = false;
                break;
            }
        }
    }
    file.close();
    return valid;
}

std::vector<std::vector<std::string>> MapSelectorState::makeMap(std::string fileName){
    std::vector<std::vector<std::string>> map;
    std::vector<std::string> mapLine;
    std::ifstream file(fileName);
    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string word; 
        while (ss >> word){
            mapLine.push_back(word);
        }
        map.push_back(mapLine);
    }
    file.close();
    return map;
}

void MapSelectorState::spawnButtons(int ammountOfMaps){
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
        optionText.setString(mapNames[i]);
        optionText.setFillColor(sf::Color::Cyan);
        optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
        optionText.setPosition(
            (optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), 
            (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/3.4)
        );
        menuOptionsText.push_back(optionText);
    }
}


MapSelectorState::MapSelectorState(gameDataRef gameData):
    gameData(gameData),
    mapToDisplayIndex(0)
{}

void MapSelectorState::init(){
    int ammountOfFiles = 0;
    for(const auto & entry : std::experimental::filesystem::directory_iterator(mapFolderLocation)){
        if(entry.path().extension().u8string() == ".txt"){
            if(isValidFile(entry.path().u8string())){
                if(ammountOfFiles >= 5){
                    break;
                }else{
                    ammountOfFiles++;
                }
                std::string fileName = entry.path().u8string();
                std::vector<std::vector<std::string>> map = makeMap(entry.path().u8string());
                TileMap tileMap(sf::Vector2f(500, 100), sf::Vector2f(500, 500), map, sf::Vector2u(map.size(), map[0].size()));
                tileMapVector.push_back(tileMap)


                fileName = fileName.substr(15, fileName.length()-19);
                if(fileName.length() > 16){
                    fileName = fileName.substr(0, 13);
                    fileName = fileName.append("...");
                }
                mapNames.push_back(fileName);
            }
        }
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
    
    
    int ammountOfMaps = mapNames.size();
    spawnButtons(ammountOfMaps);
    // sf::Vector2f mapSelectorStateOptionSize = sf::Vector2f( 
	// 	static_cast< float >( gameData->assetManager.getTexture("mapSelectorState option").getSize().x ), 
	// 	static_cast< float >( gameData->assetManager.getTexture("mapSelectorState option").getSize().y )
	// );
    // for(unsigned int i=0; i<ammountOfMaps; i++){
    //     sf::Sprite optionSprite;
    //     optionSprite.setTexture(gameData->assetManager.getTexture("mapSelectorState option"));
    //     optionSprite.setScale(
    //         (gameData->window.getSize().x/mapSelectorStateOptionSize.x)/5, 
    //         (gameData->window.getSize().y/mapSelectorStateOptionSize.y)/10
    //     );
    //     optionSprite.setPosition(
    //         (gameData->window.getSize().x/20), 
    //         ((gameData->window.getSize().y/10) - (optionSprite.getGlobalBounds().height/5) 
    //             + (i*((gameData->window.getSize().y/5) - (optionSprite.getGlobalBounds().height/5))))
    //     );
    //     menuOptions.push_back(optionSprite);
    // 
    //     sf::Text optionText;
    //     optionText.setFont(gameData->assetManager.getFont("default font"));
    //     optionText.setString(mapNames[i]);
    //     optionText.setFillColor(sf::Color::Cyan);
    //     optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
    //     optionText.setPosition(
    //         (optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), 
    //         (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/3.4)
    //     );
    //     menuOptionsText.push_back(optionText);
    // }
    
}


void MapSelectorState::handleInput(){
    sf::Event event;

    while(gameData->window.pollEvent(event)){
        if( event.type == sf::Event::Closed ){
            gameData->window.close();
        }
        for(unsigned short int i=0; i<menuOptions.size(); i++){
            if(gameData->inputManager.isSpriteClicked(menuOptions[i], sf::Mouse::Left, gameData->window)){
                mapToDisplayIndex = i;
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
    gameData->window.draw(tileMapVector[mapToDisplayIndex]);

    gameData->window.display();
}
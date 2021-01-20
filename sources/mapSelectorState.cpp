#include "../headers/mapSelectorState.hpp"

MapSelectorState::MapSelectorState(gameDataRef gameData):
    gameData(gameData),
    mapToDisplayIndex(0)
{}

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
    std::vector<std::vector<std::string>> map = {};
    std::ifstream file(fileName);
    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> mapLine = {};
        std::istringstream ss(line);
        std::string word; 
        while (ss >> word){
            mapLine.push_back(word);
        }
        map.push_back(mapLine);
    }
    // to add: reverse the map
    // std::vector<std::vector<std::string>> reverseMap = map;
    // for (unsigned int i = 0; i < map.size(); i++){
    //     for (unsigned int j = 0; j < map[i].size(); j++){
    //         reverseMap[j][i] = map[i][j];
    //     }
        
    // }
    
    file.close();
    return map;
}

void MapSelectorState::spawnMapButtons(){
    sf::Vector2f mapSelectorStateOptionSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("default button").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("default button").getSize().y )
	);
    for(unsigned int i=0; i<mapNames.size(); i++){
        sf::Sprite optionSprite;
        optionSprite.setTexture(gameData->assetManager.getTexture("default button"));
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
        optionText.setFillColor(sf::Color(255, 194, 0));
        optionText.setStyle(sf::Text::Bold);
        optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
        optionText.setPosition(
            (optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), 
            (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/3)
        );
        menuOptionsText.push_back(optionText);
    }
}

void MapSelectorState::init(){
    int ammountOfFiles = 0;

    gameData->assetManager.loadTexture("solid", Resource::solid);
    gameData->assetManager.loadTexture("break", Resource::breakable);
    gameData->assetManager.loadTexture("play1", Resource::play1);
    gameData->assetManager.loadTexture("play2", Resource::play2);
    gameData->assetManager.loadTexture("background", Resource::mapBackground);
    gameData->assetManager.loadTexture("empty", Resource::solid);

    for(const auto & entry : std::experimental::filesystem::directory_iterator(Resource::mapFolderLocation)){
        if(entry.path().extension().u8string() == ".txt"){
            if(isValidFile(entry.path().u8string())){
                if(ammountOfFiles >= 5){
                    break;
                }else{
                    ammountOfFiles++;
                }
                std::string fileName = entry.path().u8string();
                std::vector<std::vector<std::string>> map = makeMap(entry.path().u8string());
                //to add: scalable dimentions v
                TileMap tileMap(
                    sf::Vector2f(Resource::screenWidth/7*3, Resource::screenHeight/5), 
                    sf::Vector2f(Resource::screenHeight/5*3, Resource::screenHeight/5*3), 
                    gameData, 
                    map,
                    sf::Vector2u(map.size(), map[0].size())
                );
                tileMapVector.push_back(tileMap);


                fileName = fileName.substr(15, fileName.length()-19);
                if(fileName.length() > 16){
                    fileName = fileName.substr(0, 13);
                    fileName = fileName.append("...");
                }
                mapNames.push_back(fileName);
            }
        }
    }
        
    background.setTexture(gameData->assetManager.getTexture("default background"));
    sf::Vector2f mapSelectorStateBackgroundSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().y )
	);
    background.setScale(
        gameData->window.getSize().x/mapSelectorStateBackgroundSize.x, 
        gameData->window.getSize().y/mapSelectorStateBackgroundSize.y
    );
    
    spawnMapButtons();

    playButton.setTexture(gameData->assetManager.getTexture("default button"));
    playButton.setPosition(Resource::screenWidth/7*4.4, Resource::screenHeight/5*4.25);
    playButton.setScale(
        (gameData->window.getSize().x/gameData->assetManager.getTexture("default button").getSize().x)/5, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("default button").getSize().y)/10
    );
    playButtonText.setFont(gameData->assetManager.getFont("default font"));
    playButtonText.setString("Play");
    playButtonText.setFillColor(sf::Color(255, 194, 0));
    playButtonText.setStyle(sf::Text::Bold);
    playButtonText.setOrigin(playButtonText.getGlobalBounds().width/2, playButtonText.getGlobalBounds().height/2);
    playButtonText.setPosition(
            (playButton.getPosition().x)+(playButton.getGlobalBounds().width/2), 
            (playButton.getPosition().y)+(playButton.getGlobalBounds().height/3)
    );

    returnButton.setTexture(gameData->assetManager.getTexture("default button"));
    returnButton.setPosition(Resource::screenWidth/7*2.8, Resource::screenHeight/5*4.25);
    returnButton.setScale(
        (gameData->window.getSize().x/gameData->assetManager.getTexture("default button").getSize().x)/5, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("default button").getSize().y)/10
    );
    returnButtonText.setFont(gameData->assetManager.getFont("default font"));
    returnButtonText.setString("Back");
    returnButtonText.setFillColor(sf::Color(255, 194, 0));
    returnButtonText.setStyle(sf::Text::Bold);
    returnButtonText.setOrigin(returnButtonText.getGlobalBounds().width/2, returnButtonText.getGlobalBounds().height/2);
    returnButtonText.setPosition(
        (returnButton.getPosition().x)+(returnButton.getGlobalBounds().width/2), 
        (returnButton.getPosition().y)+(returnButton.getGlobalBounds().height/3)
    );
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
        if(gameData->inputManager.isSpriteClicked(playButton, sf::Mouse::Left, gameData->window)){
            // std::cout << "go to inGameState" << std::endl;
            gameData->tileMap = tileMapVector[mapToDisplayIndex];
            gameData->stateMachine.addState(std::make_unique<InGameState>(gameData));
        }
        if(gameData->inputManager.isSpriteClicked(returnButton, sf::Mouse::Left, gameData->window)){
            gameData->stateMachine.removeState();
        } 
    }
}

void MapSelectorState::update(float deltaTime){
    (void)deltaTime;
}

void MapSelectorState::draw(float deltaTime){
    (void)deltaTime;
    gameData->window.clear();

    gameData->window.draw(background);
    gameData->window.draw(playButton);
    gameData->window.draw(playButtonText);
    gameData->window.draw(returnButton);
    gameData->window.draw(returnButtonText);
    for(unsigned short int i=0; i<menuOptions.size(); i++){
        gameData->window.draw(menuOptions[i]);
        gameData->window.draw(menuOptionsText[i]);
    }
    tileMapVector[mapToDisplayIndex].draw(true);

    gameData->window.display();
}
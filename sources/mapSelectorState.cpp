#include "../headers/mapSelectorState.hpp"

MapSelectorState::MapSelectorState(gameDataRef gameData):
    gameData{gameData},
    selectedMapIndex{},
    tileMapPreviewAvailable{true}
{}

void MapSelectorState::init() {
    gameData->assetManager.loadTexture("solid", Resource::solid);
    gameData->assetManager.loadTexture("break", Resource::breakable);
    gameData->assetManager.loadTexture("spawn", Resource::spawn);
    gameData->assetManager.loadTexture("background", Resource::mapBackground);
    gameData->assetManager.loadTexture("empty", Resource::solid);

    if(gameData->multiplayer){
        mThread = std::thread(&MapSelectorState::lobbyQueue, this);
    }

    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(gameData->window.getSize() / bgTexture.getSize());

    mapStore = mapLoader.loadTileMaps(gameData,
        Resource::screenSize * sf::Vector2f{40/100.f, 10/100.f},
        Resource::screenHeight * sf::Vector2f{70/100.f, 70/100.f}
    );
    spawnMapButtons();

    playButton.setTexture(gameData->assetManager.getTexture("default button"));
    playButton.setPosition(Resource::screenWidth/7*4.4, Resource::screenHeight/5*4.25);
    playButton.setScale(
        (gameData->window.getSize().x/gameData->assetManager.getTexture("default button").getSize().x)/5.0f, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("default button").getSize().y)/10.0f
    );
    playButtonText.setFont(gameData->assetManager.getFont("default font"));
    playButtonText.setString("Play");
    playButtonText.setFillColor(Resource::Button::defaultFontColor);
    playButtonText.setStyle(sf::Text::Bold);
    playButtonText.setOrigin(playButtonText.getGlobalBounds().width/2, playButtonText.getGlobalBounds().height/2);
    playButtonText.setPosition(
            (playButton.getPosition().x)+(playButton.getGlobalBounds().width/2), 
            (playButton.getPosition().y)+(playButton.getGlobalBounds().height/2.2)
    );

    returnButton.setTexture(gameData->assetManager.getTexture("default button"));
    returnButton.setPosition(Resource::screenWidth/7*2.8, Resource::screenHeight/5*4.25);
    returnButton.setScale(
        (gameData->window.getSize().x/gameData->assetManager.getTexture("default button").getSize().x)/5.0f, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("default button").getSize().y)/10.0f
    );
    returnButtonText.setFont(gameData->assetManager.getFont("default font"));
    returnButtonText.setString("Back");
    returnButtonText.setFillColor(Resource::Button::defaultFontColor);
    returnButtonText.setStyle(sf::Text::Bold);
    returnButtonText.setOrigin(returnButtonText.getGlobalBounds().width/2, returnButtonText.getGlobalBounds().height/2);
    returnButtonText.setPosition(
        (returnButton.getPosition().x)+(returnButton.getGlobalBounds().width/2), 
        (returnButton.getPosition().y)+(returnButton.getGlobalBounds().height/2.2)
    );

    playButtonMultiplayer.setTexture(gameData->assetManager.getTexture("default button"));
    playButtonMultiplayer.setPosition(Resource::screenWidth/7*4.4, Resource::screenHeight/5*4.25);
    playButtonMultiplayer.setScale(
        (gameData->window.getSize().x/gameData->assetManager.getTexture("default button").getSize().x)/5.0f, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("default button").getSize().y)/10.0f
    );
    playButtonMultiplayerText.setFont(gameData->assetManager.getFont("default font"));
    playButtonMultiplayerText.setString("Start online");
    playButtonMultiplayerText.setFillColor(Resource::Button::defaultFontColor);
    playButtonMultiplayerText.setStyle(sf::Text::Bold);
    playButtonMultiplayerText.setOrigin(playButtonMultiplayerText.getGlobalBounds().width/2, playButtonMultiplayerText.getGlobalBounds().height/2);
    playButtonMultiplayerText.setPosition(
        (playButtonMultiplayer.getPosition().x)+(playButtonMultiplayer.getGlobalBounds().width/2), 
        (playButtonMultiplayer.getPosition().y)+(playButtonMultiplayer.getGlobalBounds().height/2.2)
    );
    
}

void MapSelectorState::spawnMapButtons(){
    sf::Vector2f mapSelectorStateOptionSize = sf::Vector2f( 
        static_cast< float >( gameData->assetManager.getTexture("default button").getSize().x ), 
        static_cast< float >( gameData->assetManager.getTexture("default button").getSize().y )
    );
    for(unsigned int i=0; i<mapStore.size(); i++){
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
        optionText.setString(Util::ellipseString(mapStore[i].name, 12)); // change literal
        optionText.setFillColor(Resource::Button::defaultFontColor);
        optionText.setStyle(sf::Text::Bold);
        optionText.setOrigin(optionText.getGlobalBounds().width/2, optionText.getGlobalBounds().height/2);
        optionText.setPosition(
            (optionSprite.getPosition().x)+(optionSprite.getGlobalBounds().width/2), 
            (optionSprite.getPosition().y)+(optionSprite.getGlobalBounds().height/2.2)
        );
        menuOptionsText.push_back(optionText);
    }
}

void MapSelectorState::handleInput() {
    sf::Event event;

    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        for (auto index = 0u; index < menuOptions.size(); ++index) {
            if (gameData->inputManager.isSpriteClicked(
                menuOptions[index], sf::Mouse::Left, gameData->window)
            ) {
                selectedMapIndex = index;
            }
        }
        if (gameData->inputManager.isSpriteClicked(playButton, sf::Mouse::Left, gameData->window) && !gameData->multiplayer){
            tileMapPreviewAvailable = false;
            gameData->tileMap = std::move(mapStore[selectedMapIndex].tileMap);
            return gameData->stateMachine.addState(std::make_unique<InGameState>(gameData));
        }
        if (gameData->inputManager.isSpriteClicked(
            returnButton, sf::Mouse::Left, gameData->window)
        ) {
            gameData->stateMachine.removeState();
        }
        if(gameData->inputManager.isSpriteClicked(playButtonMultiplayer, sf::Mouse::Left, gameData->window) && gameData->multiplayer){
            tileMapPreviewAvailable = false;
            gameData->tileMap = std::move(mapStore[selectedMapIndex].tileMap);
            gameData->server.hostReady(gameData->tileMap.getLayoutMap());
            return gameData->stateMachine.addState(std::make_unique<InGameState>(gameData));
        } 
    }
}

void MapSelectorState::update(float){
    if(startGame){
        mThread.join();
        gameData->stateMachine.addState(std::make_unique<InGameState>(gameData)); 
        startGame = false;
    }
}

void MapSelectorState::draw(float) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(returnButton);
    gameData->window.draw(returnButtonText);

    if(gameData->multiplayer){
        gameData->window.draw(playButtonMultiplayer);
        gameData->window.draw(playButtonMultiplayerText);
    }else{
        gameData->window.draw(playButton);
        gameData->window.draw(playButtonText);
    }
    
    for (auto index = 0u; index < menuOptions.size(); ++index) {
        gameData->window.draw(menuOptions[index]);
        gameData->window.draw(menuOptionsText[index]);
    }
    if (tileMapPreviewAvailable) {
        mapStore[selectedMapIndex].tileMap.draw(true);
    }
    gameData->window.display();
}

void MapSelectorState::lobbyQueue(){
    gameData->server.receiveDataLobby(false); 
    startGame = true;
}

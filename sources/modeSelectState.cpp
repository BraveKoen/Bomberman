#include "../headers/modeSelectState.hpp"

ModeSelectState::ModeSelectState(gameDataRef gameData):
    gameData{gameData},
    showPlayerNumberButtons{false}
{}

void ModeSelectState::init() {
    sf::Time transitionTime = sf::milliseconds(100);
    gameData->assetManager.loadTexture("solid", Resource::solid);
    gameData->assetManager.loadTexture("break", Resource::breakable);
    gameData->assetManager.loadTexture("spawn", Resource::spawn);
    gameData->assetManager.loadTexture("background", Resource::mapBackground);
    gameData->assetManager.loadTexture("empty", Resource::solid);
    gameData->assetManager.loadTexture("player4", Resource::player4);
    sf::sleep(transitionTime);
    mThread = std::thread(&ModeSelectState::lobbyQueue, this);

    const auto& windowSize = gameData->window.getSize();
    stateData["showPlayerNumberButtons"]=false;
    stateData["showReadyButton"]=false;

    const std::vector menuButtonsData{
        buttonDataExt{"Local", [&showButtons = showPlayerNumberButtons](gameDataRef){showButtons=true;}},
        buttonDataExt{"Online", [&showButtons = showPlayerNumberButtons](gameDataRef){std::cout << "Online Multiplayer WIP" << std::endl; showButtons=false;}},
        buttonDataExt{"Back", [](gameDataRef gameData){sf::sleep(sf::milliseconds(100)); gameData->stateMachine.removeState();}}
    };
    const std::vector playerNumberButtonsData{
        buttonDataExt{"2 Players", [](gameDataRef gameData){gameData->playerCount=2; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},
        buttonDataExt{"3 Players", [](gameDataRef gameData){gameData->playerCount=3; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},  //Maybe highlight button and show a "map select" button instead or smth
        buttonDataExt{"4 Players", [](gameDataRef gameData){gameData->playerCount=4; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}}
    };

    const std::vector readyButtonData{
        buttonData{"Ready", [](gameDataRef gameData){gameData->server.playerReady();}}
    };
    menuButtons = makeButtons(menuButtonsData);
    playerNumberButtons = makeButtons(playerNumberButtonsData, sf::Vector2f(menuButtons[0].getSprite().getGlobalBounds().width*1.1, 0));
    readyButton = makeButtons(readyButtonData, sf::Vector2f(menuButtons[0].getSprite().getGlobalBounds().width*1.1, 0));
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(windowSize / bgTexture.getSize());
}

void ModeSelectState::handleInput() {
    sf::Event event;
    
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type
            or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) // remove or change later
        ) {
            gameData->window.close();
        }
        for (auto const& button : menuButtons) {
            if (gameData->inputManager.isSpriteClicked(
                button.getSprite(), sf::Mouse::Left, gameData->window)
            ) {
                button.invokeAction(gameData);
            }
        }
        if(showPlayerNumberButtons){
            for (auto const& button : playerNumberButtons) {
                if (gameData->inputManager.isSpriteClicked(
                    button.getSprite(), sf::Mouse::Left, gameData->window)
                ) {
                    button.invokeAction(gameData);
                }
            }
        }
        if(stateData.at("showReadyButton")){
            for (auto const& button : readyButton) {
                if (gameData->inputManager.isSpriteClicked(
                    button.getSprite(), sf::Mouse::Left, gameData->window)
                ) {
                    button.invokeAction(gameData);
                }
            }
        }
        
    }
}

void ModeSelectState::update(float) {
        if(startMul){
            for(auto i : gameData->server.getMap()){
                std::cout << std::endl;
                for(auto j : i){
                    std::cout << j;
                }
            }

            mThread.join();
            TileMap TileMap(sf::Vector2f(Resource::screenWidth/7*3, Resource::screenHeight/5), sf::Vector2f(Resource::screenHeight/5*3, Resource::screenHeight/5*3), 
            gameData, 
            gameData->server.getMap(),
            sf::Vector2u(15, 15));
            gameData->tileMap = TileMap;
            gameData->stateMachine.addState(std::make_unique<InGameState>(gameData));
    }

}

void ModeSelectState::draw(float) {
    gameData->window.clear();
    gameData->window.draw(background);

    for (const auto& button : menuButtons) {
        button.draw(gameData->window);
    }
    if(showPlayerNumberButtons){
        for (auto const& button : playerNumberButtons) {
            button.draw(gameData->window);
        }
    }
    if(stateData.at("showReadyButton")){
        for (auto const& button : readyButton) {
            button.draw(gameData->window);
        }
    }
    gameData->window.display();
}

std::vector<MenuButtonExt> ModeSelectState::makeButtons(std::vector<buttonDataExt> buttonData, sf::Vector2f offset){
    std::vector<MenuButtonExt> buttons;
    const auto& windowSize = gameData->window.getSize();
    for (std::size_t index = 0; index < buttonData.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        sf::Sprite sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRectMargin(windowSize, spriteBounds, index, buttonData.size()));
        sprite.move(offset);

        static const auto& font = gameData->assetManager.getFont("default font");
        sf::Text text{buttonData[index].title, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.5}));

        buttons.emplace_back(std::move(sprite), std::move(text), buttonData[index].action);
    }
    return buttons;
}

void ModeSelectState::lobbyQueue(){
    gameData->server.receiveDataLobby();
    std::cout << "gameStarted!" << std::endl;
    if(gameData->server.getPlayerId() == 1){
        gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));
    }else{
        startMul = true;
    }  
}
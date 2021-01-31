#include "../headers/modeSelectState.hpp"

ModeSelectState::ModeSelectState(gameDataRef gameData):
    gameData{gameData},
    showPlayerNumberButtons{false},
    showOnlineNumberButtons{false}
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
    
    const auto& windowSize = gameData->window.getSize();
    const std::vector menuButtonsData{
        ButtonDataExt{"Local", [&](){showPlayerNumberButtons=true; showOnlineNumberButtons=false; }},
        ButtonDataExt{"Online", [&](){showPlayerNumberButtons=false; showOnlineNumberButtons=true;}},
        ButtonDataExt{"Back", [&](){sf::Time transitionTime = sf::seconds(0.1f); sf::sleep(transitionTime); gameData->stateMachine.removeState();}}
    };
    const std::vector playerNumberButtonsData{
        ButtonDataExt{"2 Players", [&](){gameData->playerCount=2; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},
        ButtonDataExt{"3 Players", [&](){gameData->playerCount=3; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},  //Maybe highlight button and show a "map select" button instead or smth
        ButtonDataExt{"4 Players", [&](){gameData->playerCount=4; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}}
    };

    const std::vector readyButtonData{
        ButtonDataExt{"Join online", [&](){gameData->multiplayer = true;gameData->server.playerReady();}},
        ButtonDataExt{"Connected!", [&](){}}
    };
    menuButtons = makeButtons(menuButtonsData);
    playerNumberButtons = makeButtons(playerNumberButtonsData, sf::Vector2f(menuButtons[0].getSprite().getGlobalBounds().width*1.1, 0));
    readyButton = makeButtons(readyButtonData, sf::Vector2f(menuButtons[0].getSprite().getGlobalBounds().width*1.1, 0));
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(windowSize / bgTexture.getSize());
}

void ModeSelectState::handleInput(){
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
        if(showOnlineNumberButtons){
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

void ModeSelectState::update(float){
    if(gameData->multiplayer && oneTimePress){
        oneTimePress = false;
        mThread = std::thread(&ModeSelectState::lobbyQueue, this);
    }
    if(startMul){
        mThread.join();
        gameData->tileMap = TileMap(gameData, sf::Vector2f(Resource::screenWidth/7*3, Resource::screenHeight/5), sf::Vector2f(Resource::screenHeight/5*3, Resource::screenHeight/5*3), gameData->server.getMap());
        gameData->stateMachine.addState(std::make_unique<InGameState>(gameData)); 
        std::cout << "inGame!" << std::endl;
        startMul = false;
        oneTimePress = true;
    }
    if(startMapSelect){
        mThread.join();
        gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));
        startMapSelect = false;
        oneTimePress = true;
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
    if(showOnlineNumberButtons){
        if(gameData->server.getPlayerId() != -1){
            readyButton[1].draw(gameData->window);
        }else{
            readyButton[0].draw(gameData->window);
        }
    }
    gameData->window.display();
}

std::vector<MenuButtonExt> ModeSelectState::makeButtons(std::vector<ButtonDataExt> ButtonData, sf::Vector2f offset){
    std::vector<MenuButtonExt> buttons;
    const auto& windowSize = gameData->window.getSize();
    for (std::size_t index = 0; index < ButtonData.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        sf::Sprite sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRectMargin(windowSize, spriteBounds, index, ButtonData.size()));
        sprite.move(offset);

        static const auto& font = gameData->assetManager.getFont("default font");
        sf::Text text{ButtonData[index].title, font};
        text.setFillColor(Resource::Button::defaultFontColor);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.2}));
        buttons.emplace_back(std::move(sprite), std::move(text), ButtonData[index].action);
    }
    return buttons;
}

void ModeSelectState::lobbyQueue(){
    gameData->server.receiveDataLobby();
    if(gameData->server.getPlayerId() == 1){
        startMapSelect = true;
    }else{
        startMul = true;
        std::cout << "gameStarted!" << std::endl;
    }  
}
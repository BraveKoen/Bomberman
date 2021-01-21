#include "../headers/inGameState.hpp"
#include "../headers/tileMap.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData{gameData}
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("player1", Resource::player1);
    gameData->assetManager.loadTexture("player2", Resource::player2);
    gameData->assetManager.loadTexture("player3", Resource::player3);
    gameData->assetManager.loadTexture("player4", Resource::player4);
    //gameData->assetManager.loadTexture("opponent", Resource::play2); //More opponent stuff, this is all for the yet-to-be-implemented online multiplayer
    gameData->assetManager.loadTexture("biem", Resource::biem);
    gameData->assetManager.loadTexture("bomb spritesheet", Resource::bombSpritesheet);

    background.setTexture(gameData->assetManager.getTexture("default background"));
    background.setScale(
        gameData->window.getSize().x/gameData->assetManager.getTexture("default background").getSize().x, 
        gameData->window.getSize().y/gameData->assetManager.getTexture("default background").getSize().y
    );
    
    
    
    bHandler = std::make_shared<BombHandler>(gameData);

    gameData->tileMap.setTileMapPosition(sf::Vector2f(0, 0));
    gameData->tileMap.setTileMapSize(sf::Vector2f(Resource::screenHeight, Resource::screenHeight));

    std::vector<ControlScheme> controlSchemes;

    controlSchemes.push_back(ControlScheme(sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::Space));
    controlSchemes.push_back(ControlScheme(sf::Keyboard::Key::Up, sf::Keyboard::Key::Left, sf::Keyboard::Key::Down, sf::Keyboard::Key::Right, sf::Keyboard::Key::RControl));
    controlSchemes.push_back(ControlScheme(sf::Keyboard::Key::I, sf::Keyboard::Key::J, sf::Keyboard::Key::K, sf::Keyboard::Key::L, sf::Keyboard::Key::RAlt));
    controlSchemes.push_back(ControlScheme(sf::Keyboard::Key::Numpad8, sf::Keyboard::Key::Numpad4, sf::Keyboard::Key::Numpad5, sf::Keyboard::Key::Numpad6, sf::Keyboard::Key::Enter));

    std::vector<sf::Vector2u> spawnLocations = gameData->tileMap.searchForType("spawn");
    sf::Vector2f spawnLocation = sf::Vector2f{0, 0};
    //sf::Vector2f spawnLocOpponent = sf::Vector2f{200, 0};   //Not really sure how opponents are going to work, will treat mostly like normal player for now

    //opponents.push_back(std::make_unique<Opponent>(gameData, bHandler, spawnLocOpponent)); //Presumably only a thing in multiplayer mode

    for(int i = 0; i < gameData->playerCount; i++){
        if(i>3){
            std::cout<<"Max 4 players supported!"<<std::endl;
            break;
        }
        if(spawnLocations.size() > 0){
            spawnLocation = gameData->tileMap.tilePosToScreenPos(spawnLocations[0]);
            spawnLocations.erase(spawnLocations.begin());
            //spawnLocOpponent = gameData->tileMap.tilePosToScreenPos(spawnLocations[1]); Kind of just ignoring opponents for now
        }
        std::string textureName = "player";
        textureName.append(std::to_string(i+1));
        players.push_back(std::make_unique<Player>(gameData, bHandler, controlSchemes[i], spawnLocation, textureName, Resource::defaultPlayerMoveSpeed * (gameData->tileMap.getTileMapSize().x / gameData->tileMap.getMapSize().x)));
    }
}

void InGameState::handleInput(){
    sf::Event event;

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
    for (const auto& player : players) {
        player->handleInput();
    }
}

void InGameState::update(float delta) {
    (void)delta;
    for (const auto& player : players) {
        player->update(delta);
    }
}

void InGameState::draw(float delta) {
    (void)delta;
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->tileMap.draw();

    bHandler->update();
    bHandler->draw();

    for (const auto &player : players) {
        player->draw();
    }

    for (const auto &opponent : opponents) {
        opponent->draw();
    }
    gameData->window.display();
}

#include "../headers/inGameState.hpp"
#include "../headers/tileMap.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData{gameData}
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("player", Resource::play1);
    gameData->assetManager.loadTexture("opponent", Resource::play2);
    gameData->assetManager.loadTexture("dynamite", Resource::dynamite);
    gameData->assetManager.loadTexture("biem", Resource::biem);

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

    auto posTileMap = gameData->tileMap.searchForType("play1");
    auto spawnLocPlayer = sf::Vector2f{0, 0};
    auto spawnLocOpponent = sf::Vector2f{200, 0};
    if(posTileMap.size() > 0){

        spawnLocPlayer = gameData->tileMap.tilePosToScreenPos(posTileMap[0]);
        spawnLocOpponent = gameData->tileMap.tilePosToScreenPos(posTileMap[1]);
        
    }

    players.push_back(std::make_unique<Player>(gameData, bHandler, false, spawnLocPlayer));             //Some scuffed merge stuff here needs fix
    opponents.push_back(std::make_unique<Opponent>(gameData, bHandler, spawnLocOpponent));

    background.setTexture(gameData->assetManager.getTexture("default background"));
    sf::Vector2f mapSelectorStateBackgroundSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().y )
	);
    background.setScale(
        gameData->window.getSize().x/mapSelectorStateBackgroundSize.x, 
        gameData->window.getSize().y/mapSelectorStateBackgroundSize.y
    );
    for(int i = 0; i <= gameData->playerCount; i++){
        if(i>3){
            std::cout<<"Max 4 players supported!"<<std::endl;
            break;
        }
        players.push_back(std::make_unique<Player>(gameData, bHandler, controlSchemes[i], spawnLoc));
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

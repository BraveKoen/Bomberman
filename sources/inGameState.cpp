#include "../headers/inGameState.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData(gameData)
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("Player", Resource::play1);
    gameData->assetManager.loadTexture("Dynamite", Resource::dynamite);
    gameData->assetManager.loadTexture("Biem", Resource::biem);
    
    bHandler = std::make_shared<BombHandler>(gameData);
    players.push_back(std::make_unique<Player>(gameData, bHandler, 0));
    
    bool lol = 0;
    for(int i; i <= gameData->playerCount; i ++){
        players.push_back(std::make_unique<Player>(gameData, bHandler, lol));
        lol = true;
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
    gameData->tileMap.setTileMapPosition(sf::Vector2f(0, 0));
    gameData->tileMap.setTileMapSize(sf::Vector2f(Resource::screenHeight, Resource::screenHeight));
}

void InGameState::handleInput(){
        sf::Event event;
    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type){
            gameData->window.close();
        }
    }   
}

void InGameState::update(float delta){
    (void)delta;
    for(auto &player : players){
        player->playerMove();
        player->update();
    }
    return;
}

void InGameState::draw(float delta){
    (void)delta;
    gameData->window.clear();
    gameData->window.draw(background); //idk of dit handig is
    drawTileMap(gameData->tileMap , gameData, true);

    bHandler->update();
    bHandler->draw();

    for(auto &player : players){
        player->draw();
    }

    gameData->window.display();
}

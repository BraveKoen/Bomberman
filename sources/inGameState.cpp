#include "../headers/inGameState.hpp"
#include "../headers/tileMap.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData{gameData}
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("player", Resource::play1);
    gameData->assetManager.loadTexture("dynamite", Resource::dynamite);
    gameData->assetManager.loadTexture("biem", Resource::biem);
    gameData->assetManager.loadTexture("bomb", Resource::bombSprite);
    
    bHandler = std::make_shared<BombHandler>(gameData);

    gameData->tileMap.setTileMapPosition(sf::Vector2f(0, 0));
    gameData->tileMap.setTileMapSize(sf::Vector2f(Resource::screenHeight, Resource::screenHeight));

    //needs to be fixed! 
    bool useArrowKeys = 0;

    auto posTileMap = gameData->tileMap.searchForType("play1");
    auto spawnLoc = sf::Vector2f{0, 0};
    if(posTileMap.size() > 0){
        spawnLoc = gameData->tileMap.tilePosToScreenPos(posTileMap[0]);
    }

    for(int i = 0; i <= gameData->playerCount; i++){
        players.push_back(std::make_unique<Player>(gameData, bHandler, useArrowKeys, spawnLoc));
        useArrowKeys = true;
    }

    //needs to be fixed! 
    background.setTexture(gameData->assetManager.getTexture("default background"));
    sf::Vector2f mapSelectorStateBackgroundSize = sf::Vector2f( 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().x ), 
		static_cast< float >( gameData->assetManager.getTexture("default background").getSize().y )
	);
    background.setScale(
        gameData->window.getSize().x/mapSelectorStateBackgroundSize.x, 
        gameData->window.getSize().y/mapSelectorStateBackgroundSize.y
    );
}

void InGameState::handleInput(){
    sf::Event event;

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            gameData->window.close();
        }
    }
}

void InGameState::update(float delta) {
    (void)delta;
    for (const auto& player : players) {
        if (player->playerMove()
        and collision.isSpriteColliding(player->getSprite(),
            gameData->tileMap.getSurroundings(player->getPosition()))
        ) {
            player->revertMove();
        }
        player->update();
    }
}

void InGameState::draw(float delta) {
    (void)delta;
    gameData->window.clear();
    gameData->window.draw(background); //idk of dit handig is
    gameData->tileMap.draw();

    bHandler->update();
    bHandler->draw();

    for (const auto &player : players) {
        player->draw();
    }
    gameData->window.display();
}

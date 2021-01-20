#include "../headers/inGameState.hpp"
#include "../headers/tileMap.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData{gameData}
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("player", Resource::play1);
    gameData->assetManager.loadTexture("opponent", Resource::play2);
    gameData->assetManager.loadTexture("biem", Resource::biem);
    gameData->assetManager.loadTexture("bomb fuse frame 1", Resource::bombFuseSprite1);
    gameData->assetManager.loadTexture("bomb fuse frame 2", Resource::bombFuseSprite2);
    gameData->assetManager.loadTexture("bomb fuse frame 3", Resource::bombFuseSprite3);
    gameData->assetManager.loadTexture("bomb fuse frame 4", Resource::bombFuseSprite4);
    gameData->assetManager.loadTexture("bomb explosion frame 1", Resource::bombExplosionSprite1);
    gameData->assetManager.loadTexture("bomb explosion frame 2", Resource::bombExplosionSprite2);
    gameData->assetManager.loadTexture("bomb explosion frame 3", Resource::bombExplosionSprite3);
    gameData->assetManager.loadTexture("bomb explosion frame 4", Resource::bombExplosionSprite4);
    
    bHandler = std::make_shared<BombHandler>(gameData);

    gameData->tileMap.setTileMapPosition(sf::Vector2f(0, 0));
    gameData->tileMap.setTileMapSize(sf::Vector2f(Resource::screenHeight, Resource::screenHeight));

    //needs to be fixed! 
    bool useArrowKeys = 0;

    auto posTileMap = gameData->tileMap.searchForType("play1");
    auto spawnLocPlayer = sf::Vector2f{0, 0};
    auto spawnLocOpponent = sf::Vector2f{200, 0};
    if(posTileMap.size() > 0){

        spawnLocPlayer = gameData->tileMap.tilePosToScreenPos(posTileMap[0]);
        spawnLocOpponent = gameData->tileMap.tilePosToScreenPos(posTileMap[1]);
        
    }

    players.push_back(std::make_unique<Player>(gameData, bHandler, false, spawnLocPlayer));
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
        if (player->playerMove() and collision.isSpriteColliding(player->getSprite(), gameData->tileMap.getSurroundings(player->getPosition(), {"biem", "empty", "play1"}))){
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

    for (const auto &opponent : opponents) {
        opponent->draw();
    }
    gameData->window.display();
}

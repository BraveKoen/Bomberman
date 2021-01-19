#include "../headers/inGameState.hpp"

InGameState::InGameState(gameDataRef data):
    data(data)
{}

void InGameState::init(){
    // data->assetManager.loadTexture("Player", "resources/man.gif");
    data->assetManager.loadTexture("Player", Resource::playerSprite);
    data->assetManager.loadTexture("Dynamite", "resources/dynamite.png");
    
    bHandler = std::make_shared<BombHandler>(data);
    players.push_back(std::make_unique<Player>(data, bHandler, 0));
    
    bool lol = 0;
    for(int i; i <= data->playerCount; i ++){
        players.push_back(std::make_unique<Player>(data, bHandler, lol));
        lol = true;
    }
    background.setTexture(data->assetManager.getTexture("default background"));
    sf::Vector2f mapSelectorStateBackgroundSize = sf::Vector2f( 
		static_cast< float >( data->assetManager.getTexture("default background").getSize().x ), 
		static_cast< float >( data->assetManager.getTexture("default background").getSize().y )
	);
    background.setScale(
        data->window.getSize().x/mapSelectorStateBackgroundSize.x, 
        data->window.getSize().y/mapSelectorStateBackgroundSize.y
    );
}

void InGameState::handleInput(){
        sf::Event event;

    while (data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            data->window.close();
        }
    }
    
}

void InGameState::update(float delta) {
    (void)delta;
    for(auto &player : players){
        player->playerMove();
        player->update();
    }
    return;
}

void InGameState::draw(float delta) {
    (void)delta;
    data->window.clear(sf::Color::Blue);

    data->window.draw(background);
    for(auto &player : players){
        player->draw();
    }
    bHandler->update();
    bHandler->draw();
    data->window.display();
}

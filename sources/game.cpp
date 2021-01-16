#include "../headers/game.hpp"
#include "../headers/mainMenuState.hpp"

Game::Game(int width, int height, std::string title){
    gameData->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    gameData->stateMachine.addState(std::make_unique<MainMenuState>(gameData));
    gameData->assetManager.loadFont("default font", Resource::globalFont);
    gameData->assetManager.loadTexture("default background", Resource::defaultBackground);
    gameData->assetManager.loadTexture("default button", Resource::defaultButton);
    run();
}

void Game::run(){
    float newTime, frameTime, interpolation;
    float currentTime = clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (gameData->window.isOpen()){
        gameData->stateMachine.processStateChanges();

        newTime = clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if(frameTime > 0.25f) frameTime=0.25f;
        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= delta){
            gameData->stateMachine.getActiveState()->handleInput();
            gameData->stateMachine.getActiveState()->update(delta);
            accumulator -= delta;
        }
        interpolation = accumulator/delta;
        gameData->stateMachine.getActiveState()->draw(interpolation);
    }
}

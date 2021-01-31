#include "../headers/mainMenuState.hpp"
#include "../headers/modeSelectState.hpp"
#include "../headers/inputManager.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

MainMenuState::MainMenuState(gameDataRef gameData):
    gameData{gameData}
{}

void MainMenuState::init() {
    const auto& windowSize = gameData->window.getSize();
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(windowSize / bgTexture.getSize());
    gameData->assetManager.loadTexture("title", Resource::title);
    title.setTexture(gameData->assetManager.getTexture("title"));
    title.setScale(
        (gameData->window.getSize().y/gameData->assetManager.getTexture("title").getSize().y)/3.5f, 
        (gameData->window.getSize().y/gameData->assetManager.getTexture("title").getSize().y)/3.5f
    );
    title.setOrigin(
        gameData->assetManager.getTexture("title").getSize().x/2,
        gameData->assetManager.getTexture("title").getSize().y/2    
    );
    title.setPosition(gameData->window.getSize().x/2, gameData->window.getSize().y/6.0f);

    menuButtons = gameData->buttonFactory.createButtonsVertical<MenuButton>(
        gameData,
        std::vector{
            ButtonData{"Play", Util::switchState<ModeSelectState>},
            ButtonData{"Exit game", [](gameDataRef gameData){gameData->window.close();}}
        },
        50/100.f,
        1.4f
    );
}

void MainMenuState::handleInput() {
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
    }
}

void MainMenuState::update(float) {}

void MainMenuState::draw(float) {
    gameData->window.clear(sf::Color::Red);
    gameData->window.draw(background);
    gameData->window.draw(title);

    for (const auto& button : menuButtons) {
        button.draw(gameData->window);
    }
    gameData->window.display();
}

void MainMenuState::resume(){
    std::cout << "resume" << std::endl;
    gameData->multiplayer = false;
    gameData->server.setPlayerId(-1);
}

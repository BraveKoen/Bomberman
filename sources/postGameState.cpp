#include "../headers/postGameState.hpp"
#include "../headers/inputManager.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/mainMenuState.hpp" // ?
#include "../headers/inGameState.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

#include "../headers/buttonFactory.hpp"

#include <memory>

PostGameState::PostGameState(gameDataRef gameData):
    PostGameState{gameData, 0}
{}

PostGameState::PostGameState(gameDataRef gameData, uint_fast8_t winnerId):
    PostGameState{
        gameData,
        winnerId, 
        sf::Sprite{gameData->assetManager.loadTexture(Resource::HUD::profiles[winnerId])}
    }
{}

PostGameState::PostGameState(
    gameDataRef gameData,
    uint_fast8_t winnerId,
    const sf::Sprite& playerProfile
):
    gameData{gameData},
    winnerId{winnerId},
    playerProfile{std::move(playerProfile)}
{}

void PostGameState::init() {
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    const auto& windowSize = gameData->window.getSize();
    background.setScale(windowSize / bgTexture.getSize());

    const auto& defaultFont = gameData->assetManager.getFont("default font");
    title.setFont(defaultFont);
    title.setString("GAME OVER");
    title.setFillColor(sf::Color::Yellow);
    title.setCharacterSize(92);
    Util::centerOrigin(title);
    Util::centerXscaleY(windowSize, title, 11/100.f);

    Util::centerOrigin(playerProfile);
    Util::centerXscaleY(windowSize, playerProfile, 30/100.f);
    playerProfile.setScale(1.5f, 1.5f);

    winningText.setFont(defaultFont);
    winningText.setString("Player " + std::to_string(winnerId + 1) + " wins!");
    winningText.setFillColor(sf::Color::Yellow);
    winningText.setCharacterSize(48);
    Util::centerOrigin(winningText);
    Util::centerXscaleY(windowSize, winningText, 45/100.f);

    menuButtons = gameData->buttonFactory.createButtonsHorizontal<MenuButton>(
        gameData,
        std::vector{
            ButtonData{"Play Again", [](gameDataRef gameData){
                gameData->tileMap.loadMap();
                Util::replaceState<InGameState>(gameData);
            }},
            ButtonData{"Main Menu", [](gameDataRef gameData){
                gameData->stateMachine.removeState();
            }}
        },
        85/100.f
    );
}

void PostGameState::handleInput() {
    sf::Event event;

    while (gameData->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameData->window.close();
        }
        handleButtonInput();
    }
}

void PostGameState::handleButtonInput() const {
    for (auto const& button : menuButtons) {
        if (gameData->inputManager.isSpriteClicked(
            button.getSprite(), sf::Mouse::Left, gameData->window)
        ) {
            button.invokeAction(gameData);
        }
    }
}

void PostGameState::update(float) {}

void PostGameState::draw(float) {
    gameData->window.clear();
    gameData->window.draw(background);
    gameData->window.draw(title);
    gameData->window.draw(playerProfile);
    gameData->window.draw(winningText);
    drawMenuButtons();
    gameData->window.display();
}

void PostGameState::drawMenuButtons() const {
    for (const auto& menuButton : menuButtons) {
        menuButton.draw(gameData->window);
    }
}

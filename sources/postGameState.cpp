#include "../headers/postGameState.hpp"
#include "../headers/inputManager.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/mainMenuState.hpp" // ?
#include "../headers/inGameState.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

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

    winningText.setFont(defaultFont);
    winningText.setString("Player " + std::to_string(winnerId + 1) + " wins!");
    winningText.setFillColor(sf::Color::Yellow);
    winningText.setCharacterSize(48);
    Util::centerOrigin(winningText);
    Util::centerXscaleY(windowSize, winningText, 39/100.f);

    createMenuButtons(std::array{
        buttonData{"Play again", [](gameDataRef gameData){
            gameData->tileMap.loadMap();
            Util::replaceState<InGameState>(gameData);
        }},
        buttonData{"Quit", Util::replaceState<MainMenuState>}
    });
}

template<auto N>
void PostGameState::createMenuButtons(const std::array<buttonData, N>& buttons) {
    for (auto index = 0u; index < buttons.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        static const auto& windowSize = gameData->window.getSize();
        static const auto& scale = windowSize / texture.getSize() / sf::Vector2f{5, 10};
        auto sprite = sf::Sprite{texture};
        Util::centerOrigin(sprite);
        sprite.setScale(scale);
        constexpr auto spacing = 1.2f;
        static const auto& width = Util::getSize(sprite).x * spacing;
        static const auto offsetX = Util::offsetFromOrigin(windowSize.x, width, buttons.size());
        static const auto buttonY = windowSize.y * (85/100.f);
        const auto& position = sf::Vector2f{offsetX + (width * index), buttonY};
        sprite.setPosition(position);

        static const auto& font = gameData->assetManager.getFont("default font");
        auto text = sf::Text{buttons[index].title, font};
        Util::centerOrigin(text);
        static const auto& textScale = scale / 2;
        text.setScale(textScale);
        text.setPosition(position.x, position.y - 8);
        text.setFillColor(sf::Color::Cyan);

        menuButtons.emplace_back(std::move(sprite), std::move(text), buttons[index].action);
    }
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

#include "../headers/mainMenuState.hpp"

MainMenuState::MainMenuState(gameDataRef gameData):
    gameData{gameData}
{}

void MainMenuState::init() {
    // should be moved to main/game:
    gameData->assetManager.loadFont("defaultFont", Resource::globalFont);
    //
    const auto& texture = gameData->assetManager
        .loadTexture("menuButton", Resource::menuButtonFilePath);
    constexpr std::array buttons{
        std::pair<const char*, buttonFunc>{"Play", Util::switchState<MainMenuState>},
        std::pair<const char*, buttonFunc>{"Highscores", Util::switchState<MainMenuState>},
        std::pair<const char*, buttonFunc>{"Exit", [](gameDataRef gameData){gameData->window.close();}}
    };
    for (std::size_t index = 0; index < buttons.size(); ++index) {
        sf::Sprite sprite{texture};
        sprite.setScale(Util::scaleVector(gameData->window.getSize(), texture.getSize(), {5, 10}));
        sprite.setPosition(Util::centerPosition(
            gameData->window.getSize(), sprite.getGlobalBounds(), buttons.size(), index));

        sf::Text text{buttons[index].first, gameData->assetManager.getFont("defaultFont")};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::centerRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), sprite.getGlobalBounds(), {2, 2.6f}));

        menuButtons.emplace_back(std::move(sprite), std::move(text), buttons[index].second);
    }
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

void MainMenuState::update(float delta) {
    (void)delta;
}

void MainMenuState::draw(float delta) {
    gameData->window.clear(sf::Color::Red);

    for (const auto& button : menuButtons) {
        button.draw(gameData->window);
    }
    gameData->window.display();
    (void)delta;
}

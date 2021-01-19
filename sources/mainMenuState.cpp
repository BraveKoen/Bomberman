#include "../headers/mainMenuState.hpp"

MainMenuState::MainMenuState(gameDataRef gameData):
    gameData{gameData}
{}

void MainMenuState::init() {
    const auto& windowSize = gameData->window.getSize();
    using buttonData = std::pair<const char*, buttonFunc>;
    constexpr std::array buttons{
        buttonData{"Play", Util::switchState<MapSelectorState>},
        buttonData{"Highscores", Util::switchState<MainMenuState>},
        buttonData{"Exit", [](gameDataRef gameData){gameData->window.close();}}
    };
    for (std::size_t index = 0; index < buttons.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        sf::Sprite sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRect(windowSize, spriteBounds, index, buttons.size()));

        static const auto& font = gameData->assetManager.getFont("default font");
        sf::Text text{buttons[index].first, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.5}));

        menuButtons.emplace_back(std::move(sprite), std::move(text), buttons[index].second);
    }
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(windowSize / bgTexture.getSize());
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
    (void)delta;
    gameData->window.clear(sf::Color::Red);
    gameData->window.draw(background);

    for (const auto& button : menuButtons) {
        button.draw(gameData->window);
    }
    gameData->window.display();
}

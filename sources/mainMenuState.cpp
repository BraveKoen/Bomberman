#include "../headers/mainMenuState.hpp"
#include "../headers/modeSelectState.hpp"
//
#include "../headers/postGameState.hpp"
//
#include "../headers/inputManager.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

MainMenuState::MainMenuState(gameDataRef gameData):
    gameData{gameData}
{}

void MainMenuState::init() {
    // remove this:
    gameData->assetManager.loadTexture(Resource::HUD::profiles[0]);

    const auto& windowSize = gameData->window.getSize();
    constexpr std::array buttons{
        buttonData{"Play", Util::switchState<ModeSelectState>},
        buttonData{"Exit game", [](gameDataRef gameData){gameData->window.close();}}
    };
    for (std::size_t index = 0; index < buttons.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        auto sprite = sf::Sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRectMargin(windowSize, spriteBounds, index, buttons.size()));

        static const auto& font = gameData->assetManager.getFont("default font");
        auto text = sf::Text{buttons[index].title, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.5}));

        menuButtons.emplace_back(std::move(sprite), std::move(text), buttons[index].action);
    }
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

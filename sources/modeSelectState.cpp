#include "../headers/modeSelectState.hpp"

ModeSelectState::ModeSelectState(gameDataRef gameData):
    gameData{gameData},
    showPlayerNumberButtons{false}
{}

void ModeSelectState::init() {
    sf::Time transitionTime = sf::milliseconds(100);
    sf::sleep(transitionTime);

    const auto& windowSize = gameData->window.getSize();

    const std::vector menuButtonsData{
        buttonDataExt{"Local", [&showButtons = showPlayerNumberButtons](gameDataRef){showButtons=true;}},
        buttonDataExt{"Online", [&showButtons = showPlayerNumberButtons](gameDataRef){std::cout << "Online Multiplayer WIP" << std::endl; showButtons=false;}},
        buttonDataExt{"Back", [](gameDataRef gameData){sf::sleep(sf::milliseconds(100)); gameData->stateMachine.removeState();}}
    };
    const std::vector playerNumberButtonsData{
        buttonDataExt{"2 Players", [](gameDataRef gameData){gameData->playerCount=2; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},
        buttonDataExt{"3 Players", [](gameDataRef gameData){gameData->playerCount=3; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},  //Maybe highlight button and show a "map select" button instead or smth
        buttonDataExt{"4 Players", [](gameDataRef gameData){gameData->playerCount=4; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}}
    };
    menuButtons = makeButtons(menuButtonsData);
    playerNumberButtons = makeButtons(playerNumberButtonsData, sf::Vector2f(menuButtons[0].getSprite().getGlobalBounds().width*1.1, 0));
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(windowSize / bgTexture.getSize());
}

void ModeSelectState::handleInput() {
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
        if(showPlayerNumberButtons){
            for (auto const& button : playerNumberButtons) {
                if (gameData->inputManager.isSpriteClicked(
                    button.getSprite(), sf::Mouse::Left, gameData->window)
                ) {
                    button.invokeAction(gameData);
                }
            }
        }
    }
}

void ModeSelectState::update(float) {

}

void ModeSelectState::draw(float) {
    gameData->window.clear();
    gameData->window.draw(background);

    for (const auto& button : menuButtons) {
        button.draw(gameData->window);
    }
    if(showPlayerNumberButtons){
        for (auto const& button : playerNumberButtons) {
            button.draw(gameData->window);
        }
    }
    gameData->window.display();
}

std::vector<MenuButtonExt> ModeSelectState::makeButtons(std::vector<buttonDataExt> buttonData, sf::Vector2f offset){
    std::vector<MenuButtonExt> buttons;
    const auto& windowSize = gameData->window.getSize();
    for (std::size_t index = 0; index < buttonData.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        sf::Sprite sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRectMargin(windowSize, spriteBounds, index, buttonData.size()));
        sprite.move(offset);

        static const auto& font = gameData->assetManager.getFont("default font");
        sf::Text text{buttonData[index].title, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.5}));

        buttons.emplace_back(std::move(sprite), std::move(text), buttonData[index].action);
    }
    return buttons;
}
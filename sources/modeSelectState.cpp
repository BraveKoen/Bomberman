#include "../headers/modeSelectState.hpp"

ModeSelectState::ModeSelectState(gameDataRef gameData):
    gameData{gameData}
{}

void ModeSelectState::init() {
    sf::Time transitionTime = sf::seconds(0.1f);
    sf::sleep(transitionTime);

    const auto& windowSize = gameData->window.getSize();
    stateData["showPlayerNumberButtons"]=false;

    using buttonData = std::pair<const char*, buttonFunc>;
    const std::vector menuButtonsData{
        buttonData{"Local", [](gameDataRef gameData){gameData->stateMachine.getActiveState()->getStateDataRef()["showPlayerNumberButtons"]=true;}},
        buttonData{"Online", [](gameDataRef gameData){std::cout << "Online Multiplayer WIP" << std::endl; gameData->stateMachine.getActiveState()->getStateDataRef()["showPlayerNumberButtons"]=false;}},
        buttonData{"Back", [](gameDataRef gameData){sf::Time transitionTime = sf::seconds(0.1f); sf::sleep(transitionTime); gameData->stateMachine.removeState();}}
    };
    const std::vector playerNumberButtonsData{
        buttonData{"2 Players", [](gameDataRef gameData){gameData->playerCount=2; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},
        buttonData{"3 Players", [](gameDataRef gameData){gameData->playerCount=3; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}},  //Maybe highlight button and show a "map select" button instead or smth
        buttonData{"4 Players", [](gameDataRef gameData){gameData->playerCount=4; gameData->stateMachine.addState(std::make_unique<MapSelectorState>(gameData));}}
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
        if(stateData.at("showPlayerNumberButtons")){
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
    if(stateData.at("showPlayerNumberButtons")){
        for (auto const& button : playerNumberButtons) {
            button.draw(gameData->window);
        }
    }
    gameData->window.display();
}

std::map<std::string, bool>& ModeSelectState::getStateDataRef(){
    return stateData;
}

std::vector<MenuButton> ModeSelectState::makeButtons(std::vector<std::pair<const char*, buttonFunc>> buttonData, sf::Vector2f offset){
    std::vector<MenuButton> buttons;
    const auto& windowSize = gameData->window.getSize();
    for (std::size_t index = 0; index < buttonData.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        sf::Sprite sprite{texture};
        sprite.setScale(windowSize / texture.getSize() / sf::Vector2f{5, 10});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(Util::centerRectMargin(windowSize, spriteBounds, index, buttonData.size()));
        sprite.move(offset);

        static const auto& font = gameData->assetManager.getFont("default font");
        sf::Text text{buttonData[index].first, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 2.5}));

        buttons.emplace_back(std::move(sprite), std::move(text), buttonData[index].second);
    }
    return buttons;
}
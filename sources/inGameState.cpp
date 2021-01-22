#include "../headers/inGameState.hpp"
#include "../headers/menuButton.hpp"
#include "../headers/mainMenuState.hpp"
#include "../headers/tileMap.hpp"
#include "../headers/gameHud.hpp"
#include "../headers/utilities.hpp"
#include "../headers/game.hpp"

InGameState::InGameState(gameDataRef gameData):
    gameData{gameData},
    bHandler{std::make_shared<BombHandler>(gameData)}
{}

void InGameState::init(){
    gameData->assetManager.loadTexture("HUD frame", Resource::frame);
    gameData->assetManager.loadTexture("HUD small frame", Resource::smallFrame);
    gameData->assetManager.loadTexture("HUD banner", Resource::banner);
    gameData->assetManager.loadTexture("HUD profile0", Resource::profile4);
    gameData->assetManager.loadTexture("HUD profile1", Resource::profile1);
    gameData->assetManager.loadTexture("HUD profile2", Resource::profile2);
    gameData->assetManager.loadTexture("HUD profile3", Resource::profile3);
    gameData->assetManager.loadTexture("HUD live full", Resource::liveFull);
    gameData->assetManager.loadTexture("HUD live empty", Resource::liveEmpty);

    gameData->assetManager.loadTexture("player1", Resource::player1);
    gameData->assetManager.loadTexture("player2", Resource::player2);
    gameData->assetManager.loadTexture("player3", Resource::player3);
    gameData->assetManager.loadTexture("player4", Resource::player4);
    //gameData->assetManager.loadTexture("opponent", Resource::play2); //More opponent stuff, this is all for the yet-to-be-implemented online multiplayer
    gameData->assetManager.loadTexture("biem", Resource::biem);
    gameData->assetManager.loadTexture("bomb spritesheet", Resource::bombSpritesheet);

    gameHud = std::make_unique<GameHUD>(gameData);
    hudMenu.setTexture(gameData->assetManager.loadTexture("menu frame", Resource::menuFrame));
    const auto& hudFrame = gameHud->getFrameSize();
    hudMenu.setPosition({0, hudFrame.y});
    constexpr auto ratio = 6.0f;
    hudMenu.setScale(1, gameData->window.getSize().y / ratio / hudMenu.getGlobalBounds().height);
    initMenuButtons({0, hudFrame.y});

    gameData->tileMap.setTileMapPosition({hudFrame.x, 0});
    gameData->tileMap.setTileMapSize({Resource::screenHeight, Resource::screenHeight});

    std::vector<ControlScheme> controlSchemes;

    controlSchemes.emplace_back(sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::Space);
    controlSchemes.emplace_back(sf::Keyboard::Key::Up, sf::Keyboard::Key::Left, sf::Keyboard::Key::Down, sf::Keyboard::Key::Right, sf::Keyboard::Key::RControl);
    controlSchemes.emplace_back(sf::Keyboard::Key::I, sf::Keyboard::Key::J, sf::Keyboard::Key::K, sf::Keyboard::Key::L, sf::Keyboard::Key::RAlt);
    controlSchemes.emplace_back(sf::Keyboard::Key::Numpad8, sf::Keyboard::Key::Numpad4, sf::Keyboard::Key::Numpad5, sf::Keyboard::Key::Numpad6, sf::Keyboard::Key::Enter);

    std::vector<sf::Vector2u> spawnLocations = gameData->tileMap.searchForType("spawn");
    sf::Vector2f spawnLocation = sf::Vector2f{0, 0};
    //sf::Vector2f spawnLocOpponent = sf::Vector2f{200, 0};   //Not really sure how opponents are going to work, will treat mostly like normal player for now

    for(auto i = 0u; i < gameData->playerCount; ++i){
        if(i>3){
            std::cout<<"Max 4 players supported!"<<std::endl;
            break;
        }
        if(spawnLocations.size() > 0){
            spawnLocation = gameData->tileMap.tilePosToScreenPos(spawnLocations[0]);
            spawnLocations.erase(spawnLocations.begin());
            //spawnLocOpponent = gameData->tileMap.tilePosToScreenPos(spawnLocations[1]); Kind of just ignoring opponents for now
        }
        std::string textureName = "player";
        textureName.append(std::to_string(i+1));
        players.push_back(std::make_unique<Player>(gameData, bHandler, controlSchemes[i], spawnLocation, i + 1, textureName, Resource::defaultPlayerMoveSpeed * (gameData->tileMap.getTileMapSize().x / gameData->tileMap.getMapSize().x)));
    }

    //needs to be fixed! 
    const auto& bgTexture = gameData->assetManager.getTexture("default background");
    background.setTexture(bgTexture);
    background.setScale(gameData->window.getSize() / bgTexture.getSize());
    
}

void InGameState::initMenuButtons(const sf::Vector2f& offset) {
    constexpr std::array buttons{
        buttonData{"Settings", [](gameDataRef){std::cout << "settings hud menu\n";}}, // print something
        buttonData{"Quit", Util::switchState<MainMenuState>} // back to main menu
    };
    for (std::size_t index = 0; index < buttons.size(); ++index) {
        static const auto& texture = gameData->assetManager.getTexture("default button");
        auto&& sprite = sf::Sprite{texture};
        auto const& hudSize = Sprite::getSize(hudMenu);
        sprite.setScale(hudSize / texture.getSize() / sf::Vector2f{1, 3});
        const auto& spriteBounds = sprite.getGlobalBounds();
        sprite.setPosition(offset + Util::centerRect(hudSize, spriteBounds, index, buttons.size()));

        static const auto& font = gameData->assetManager.getFont("default font");
        auto&& text = sf::Text{buttons[index].title, font};
        text.setFillColor(sf::Color::Cyan);
        text.setOrigin(Util::scaleRect(text.getGlobalBounds(), {2, 2}));
        text.setPosition(Util::centerVector(sprite.getPosition(), spriteBounds, {2, 3.2}));

        menuButtons.emplace_back(std::move(sprite), std::move(text), buttons[index].action);
    }
}

void InGameState::handleInput(){
    sf::Event event;

    while (gameData->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
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
    for (const auto& player : players) {
        player->handleInput();
    }
}

void InGameState::update(float delta) {
    for (const auto& player : players) {
        player->update(delta);

        // note: change this so health bar is updated only when necessary
        gameHud->setHealthBar(gameData, player->getPlayerId() - 1, player->getHealth());
    }
}

void InGameState::draw(float) {
    gameData->window.clear();
    gameData->window.draw(background); //idk of dit handig is
    gameData->tileMap.draw();
    gameHud->draw(gameData->window);
    // gameData->window.draw(hudMenu); // fix later

    for (const auto& menuButton : menuButtons) {
        menuButton.draw(gameData->window);
    }

    bHandler->update();
    bHandler->draw();

    for (const auto &player : players) {
        player->draw();
    }

    for (const auto &opponent : opponents) {
        opponent->draw();
    }
    gameData->window.display();
}

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <memory>
#include "game-data.hpp"
#include "../menu/main-menu.hpp"

auto isEscapePressed() -> bool {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

auto runGame(gameDataRef data) -> void {
    auto const mainMenu = std::make_unique<MainMenuState>(data);
    mainMenu->init();

    while (data->window.isOpen()) {
        // ...
        mainMenu->handleInput();
        mainMenu->update(0.0f);
        mainMenu->draw(0.0f);
        // ...
        sf::sleep(sf::milliseconds(64));

        if (isEscapePressed()) {
            data->window.close();
            return;
        }
    }
}

auto main() -> int {
    auto data = std::make_shared<GameData>();
    data->window.create(
        {400, 500},
        "Bomberman - dbg",
        sf::Style::Titlebar | sf::Style::Close
    );
    runGame(data);
    return 0;
}

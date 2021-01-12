#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include "main-menu.hpp"

MainMenuState::MainMenuState(gameDataRef data):
    data(data)
{}

auto MainMenuState::init() -> void {
    // quick workaround, should invoke asset manager instead
    auto isLoaded = texture1.loadFromFile("../../resource/button-1.png");
    isLoaded |= texture2.loadFromFile("../../resource/button-2.png");
    isLoaded |= texture3.loadFromFile("../../resource/button-3.png");
    //
    if (not isLoaded) {
        std::cout << "Couldn't load textures :(\n";
        return;
    }
    button1.setTexture(texture1);
    button2.setTexture(texture2);
    button3.setTexture(texture3);

    button1.setPosition({100, 100});
    button2.setPosition({100, 200});
    button3.setPosition({100, 300});
}

auto MainMenuState::handleInput() -> void {
    sf::Event event;

    while (data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            data->window.close();
        } else if (data->input.isSpriteClicked(
                button1, sf::Mouse::Left, data->window)) {
            std::cout << "button1 was clicked\n";
        } else if (data->input.isSpriteClicked(
                button2, sf::Mouse::Left, data->window)) {
            std::cout << "button2 was clicked\n";
        } else if (data->input.isSpriteClicked(
                button3, sf::Mouse::Left, data->window)) {
            std::cout << "button3 was clicked\n";
        }
    }
}

auto MainMenuState::update(float delta) -> void {
    (void)delta;
}

auto MainMenuState::draw(float delta) -> void {
    data->window.clear(sf::Color::Red);
    data->window.draw(button1);
    data->window.draw(button2);
    data->window.draw(button3);
    data->window.display();
    (void)delta;
}

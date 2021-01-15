#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../headers/definitions.hpp"
#include "../headers/inputManager.hpp"
#include "../headers/assetManager.hpp"
#include "../headers/mainMenu.hpp"

MainMenuState::MainMenuState(gameDataRef data):
    data{data}
{}

void MainMenuState::init() {
    button1.setTexture(data->assetManager
        .loadTexture("button1", Resource::button1FilePath));
    button2.setTexture(data->assetManager
        .loadTexture("button2", Resource::button2FilePath));
    button3.setTexture(data->assetManager
        .loadTexture("button3", Resource::button3FilePath));
    button1.setPosition({100, 100});
    button2.setPosition({100, 200});
    button3.setPosition({100, 300});
}

void MainMenuState::handleInput() {
    sf::Event event;

    while (data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            data->window.close();
        } else if (data->inputManager.isSpriteClicked(
                button1, sf::Mouse::Left, data->window)) {
            std::cout << "button1 was clicked\n";
        } else if (data->inputManager.isSpriteClicked(
                button2, sf::Mouse::Left, data->window)) {
            std::cout << "button2 was clicked\n";
        } else if (data->inputManager.isSpriteClicked(
                button3, sf::Mouse::Left, data->window)) {
            std::cout << "button3 was clicked\n";
        }
    }
}

void MainMenuState::update(float delta) {
    (void)delta;
}

void MainMenuState::draw(float delta) {
    data->window.clear(sf::Color::Red);
    data->window.draw(button1);
    data->window.draw(button2);
    data->window.draw(button3);
    data->window.display();
    (void)delta;
}

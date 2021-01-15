#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "../headers/gameData.hpp"
#include "../headers/state.hpp"

class MainMenuState: public State {
private:
    gameDataRef data;
    sf::Sprite button1;
    sf::Sprite button2;
    sf::Sprite button3;
public:
    MainMenuState(gameDataRef data);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;
};

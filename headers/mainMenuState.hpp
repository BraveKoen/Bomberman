#ifndef __MAINMENUSTATE_HPP__
#define __MAINMENUSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "definitions.hpp"
#include "menuButton.hpp"
// #include "../headers/game.hpp"
// #include "../headers/state.hpp"
// #include "../headers/utilities.hpp"
// #include "../headers/definitions.hpp"
// #include "../headers/inputManager.hpp"
// #include "../headers/assetManager.hpp"
// #include "../headers/menuButton.hpp"
// #include "../headers/modeSelectState.hpp"

class MainMenuState: public State {
private:
    gameDataRef gameData;
    std::vector<MenuButton> menuButtons;
    sf::Sprite background;
    sf::Sprite title;
public:
    MainMenuState(gameDataRef gameData);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;
};

#endif // __MAINMENUSTATE_HPP__

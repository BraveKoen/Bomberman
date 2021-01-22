#ifndef __MAINMENUSTATE_HPP__
#define __MAINMENUSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "definitions.hpp"
#include "menuButton.hpp"

class MainMenuState: public State {
private:
    gameDataRef gameData;
    std::vector<MenuButton> menuButtons;
    sf::Sprite background;
public:
    MainMenuState(gameDataRef gameData);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;
};

#endif // __MAINMENUSTATE_HPP__

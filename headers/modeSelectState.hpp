#ifndef __MODESELECTSTATE_HPP__
#define __MODESELECTSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "state.hpp"
#include "utilities.hpp"
#include "definitions.hpp"
#include "menuButtonExt.hpp"
#include "mapSelectorState.hpp"

class ModeSelectState: public State {
private:
    gameDataRef gameData;
    bool showPlayerNumberButtons;

    std::vector<MenuButtonExt> menuButtons;
    std::vector<MenuButtonExt> playerNumberButtons;
    sf::Sprite background;
public:
    ModeSelectState(gameDataRef gameData);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;

    std::vector<MenuButtonExt> makeButtons(std::vector<buttonDataExt> buttonData, sf::Vector2f offset={0,0});
};

#endif // __MODESELECTSTATE_HPP__
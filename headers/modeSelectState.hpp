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
#include "menuButton.hpp"
#include "mapSelectorState.hpp"

class ModeSelectState: public State {
private:
    gameDataRef gameData;
    std::vector<MenuButton> menuButtons;
    std::vector<MenuButton> playerNumberButtons;
    sf::Sprite background;
    std::map<std::string, bool> stateData;
public:
    ModeSelectState(gameDataRef gameData);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;

    virtual std::map<std::string, bool>& getStateDataRef();

    std::vector<MenuButton> makeButtons(std::vector<std::pair<const char*, buttonFunc>> buttonData, sf::Vector2f offset={0,0});
};

#endif // __MODESELECTSTATE_HPP__
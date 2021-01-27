#ifndef __MODESELECTSTATE_HPP__
#define __MODESELECTSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <thread>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "state.hpp"
#include "utilities.hpp"
#include "definitions.hpp"
#include "menuButtonExt.hpp"
#include "mapSelectorState.hpp"
#include "tileMap.hpp"

class ModeSelectState: public State {
private:
    gameDataRef gameData;
    bool showPlayerNumberButtons;
    bool showOnlineNumberButtons;
    std::vector<MenuButtonExt> menuButtons;
    std::vector<MenuButtonExt> playerNumberButtons;
    std::vector<MenuButtonExt> readyButton;
    sf::Sprite background;
    std::map<std::string, bool> stateData;
    std::thread mThread;
    bool startMul = false;
    bool oneTimePress = true;
public:
    ModeSelectState(gameDataRef gameData);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;

    std::vector<MenuButtonExt> makeButtons(std::vector<buttonDataExt> buttonData, sf::Vector2f offset={0,0});

    void lobbyQueue();
};

#endif // __MODESELECTSTATE_HPP__
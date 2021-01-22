#ifndef __INGAMESTATE_HPP__
#define __INGAMESTATE_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread>
#include <map>

#include "player.hpp"
#include "opponent.hpp"
#include "utilities.hpp"
#include "definitions.hpp"
#include "bombHandler.hpp"
#include "controlScheme.hpp"
#include "definitions.hpp"
#include "collision.hpp"
#include "menuButton.hpp"
#include "gameHud.hpp"
#include "serverInfo.hpp"

class InGameState : public State {
public:
    InGameState(gameDataRef gameData);

    void init() override;
    void handleInput() override;
    void update(float delta) override;
    void draw(float delta) override;
    void updateOpponentLocation();
    void createOpponent();

private:
    enum class GameState {
        Running,
        Closing,
        Stopped
    };
    gameDataRef gameData;
    // std::unique_ptr<GameHUD> gameHud;
    GameHUD gameHud;
    GameState gameState;
    std::shared_ptr<BombHandler> bombHandler;
    std::vector<std::unique_ptr<Player>> players;

    std::vector<MenuButton> menuButtons;
    Collision collision;
    sf::Clock gameOverDelay;
    std::map<int, std::shared_ptr<Opponent>> mapOfEnemies;
    sf::Sprite background;
    sf::Sprite hudMenu;

    void initMenuButtons(const sf::Vector2f& offset);
    std::thread mThread;
};

#endif // __INGAMESTATE_HPP__

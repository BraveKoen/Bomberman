#ifndef __INGAMESTATE_HPP__
#define __INGAMESTATE_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

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

class InGameState : public State {
public:
    InGameState(gameDataRef gameData);

    void init() override;
    void handleInput() override;
    void update(float delta) override;
    void draw(float delta) override;
private:
    gameDataRef gameData;
    std::unique_ptr<GameHUD> gameHud;
    std::shared_ptr<BombHandler> bHandler;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Opponent>> opponents;
    std::vector<MenuButton> menuButtons;
    Collision collision;
    sf::Sprite background;
    sf::Sprite hudMenu;

    void initMenuButtons(const sf::Vector2f& offset);
};

#endif // __INGAMESTATE_HPP__

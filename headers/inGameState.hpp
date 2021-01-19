#ifndef __INGAMESTATE_HPP__
#define __INGAMESTATE_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "game.hpp"
#include "player.hpp"
#include "opponent.hpp"
#include "utilities.hpp"
#include "definitions.hpp"
#include "bombHandler.hpp"
#include "definitions.hpp"
#include "collision.hpp"

class InGameState : public State {
public:
    InGameState(gameDataRef gameData);

    void init() override;
    void handleInput() override;
    void update(float delta) override;
    void draw(float delta) override;

private:
    gameDataRef gameData;
    Collision collision;
    std::shared_ptr<BombHandler> bHandler = nullptr;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Opponent>> opponents;
    sf::Sprite background;
};

#endif // __INGAMESTATE_HPP__

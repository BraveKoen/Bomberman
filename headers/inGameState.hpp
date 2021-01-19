#ifndef __INGAMESTATE_HPP__
#define __INGAMESTATE_HPP__

#include <SFML/Graphics.hpp>
#include <vector>

#include "game.hpp"
#include "player.hpp"
#include "bombHandler.hpp"
#include "definitions.hpp"

class InGameState : public State{
public:
    InGameState(gameDataRef gameData);
    ~InGameState(){}

    void init() override;
    void handleInput() override;
    void update(float delta) override;
    void draw(float delta) override;

private:
    gameDataRef gameData;
    std::shared_ptr<BombHandler> bHandler = nullptr;
    std::vector<std::unique_ptr<Player>> players;
    sf::Sprite background;
};

#endif // __INGAMESTATE_HPP__

#ifndef __INGAMESTATE_HPP__
#define __INGAMESTATE_HPP__

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "player.hpp"

class InGameState : public State{
public:
    InGameState(gameDataRef data);
    ~InGameState(){}

    void init() override;
    void handleInput() override;
    void update(float delta) override;
    void draw(float delta) override;

private:
    gameDataRef data;
    Player *p1;
    
};

#endif // __INGAMESTATE_HPP__

#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "../dbg/game-data.hpp"
#include "../dbg/state.hpp"

class MainMenuState: public State {
private:
    sf::Sprite button1;
    sf::Sprite button2;
    sf::Sprite button3;

    // quick workaround, should invoke asset manager instead
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;
    //
    gameDataRef data;    
public:
    MainMenuState(gameDataRef data);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;
};

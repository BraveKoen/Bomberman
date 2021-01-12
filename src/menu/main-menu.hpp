#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "../dbg/game-data.hpp"
#include "../dbg/state.hpp"

class MainMenuState : public State {
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
    virtual auto init() -> void override;
    virtual auto handleInput() -> void override;
    virtual auto update(float delta) -> void override;
    virtual auto draw(float delta) -> void override;
};

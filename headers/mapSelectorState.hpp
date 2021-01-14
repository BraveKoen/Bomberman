#ifndef __MAPSELECTORSTATE_HPP__
#define __MAPSELECTORSTATE_HPP__

#include "state.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class MapSelectorState : public State{
public:
    MapSelectorState(gameDataRef gameData);

    void init();
    void handleInput();
    void update(float deltaTime);
    void draw(float deltaTime);
private:
    gameDataRef gameData;
    std::vector<sf::Text> menuOptionsText;
    sf::Sprite background;
    std::vector<sf::Sprite> menuOptions;
};

#endif // __MAPSELECTORSTATE_HPP__
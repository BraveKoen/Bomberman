#ifndef __MAPSELECTOR_HPP__
#define __MAPSELECTOR_HPP__

#include "state.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class MapSelector : public State{
public:
    MapSelector(gameDataRef gameData);

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

#endif // __MAPSELECTOR_HPP__
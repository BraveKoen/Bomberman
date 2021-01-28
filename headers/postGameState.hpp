#ifndef __POSTGAMESTATE_HPP__
#define __POSTGAMESTATE_HPP__

#include <array>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "definitions.hpp"
#include "menuButton.hpp"

class PostGameState : public State {
private:
    gameDataRef gameData;
    uint_fast8_t winnerId;
    sf::Sprite playerProfile;
    sf::Sprite background;
    sf::Text title;
    sf::Text winningText;
    std::vector<MenuButton> menuButtons;
    template<auto N>
    void createMenuButtons(const std::array<buttonData, N>& buttons);
    void drawMenuButtons() const;
    void handleButtonInput() const;
public:
    PostGameState(gameDataRef gameData);
    PostGameState(gameDataRef gameData, uint_fast8_t winnerId);
    PostGameState(gameDataRef gameData, uint_fast8_t winnerId, const sf::Sprite& playerProfile);
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float delta) override;
    virtual void draw(float delta) override;
};

#endif // __POSTGAMESTATE_HPP__

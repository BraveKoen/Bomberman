#ifndef __MENUBUTTON_HPP__
#define __MENUBUTTON_HPP__

#include <SFML/Graphics.hpp>
#include "../headers/button.hpp"
#include "../headers/game.hpp"

using buttonFunc = void (*)(gameDataRef gameData);

class MenuButton: public Button {
private:
    buttonFunc action;
public:
    MenuButton(
        const sf::Sprite& sprite,
        const sf::Text& text,
        buttonFunc action
    );
    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTON_HPP__

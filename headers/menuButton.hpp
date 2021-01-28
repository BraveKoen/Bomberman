#ifndef __MENUBUTTON_HPP__
#define __MENUBUTTON_HPP__

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

using buttonFunc = void (*)(gameDataRef gameData);
using buttonData = struct {const char* title; buttonFunc action;};

class MenuButton: public Button {
private:
    buttonFunc action;
public:
    MenuButton(const sf::Sprite& sprite, const sf::Text& text, buttonFunc action);
    MenuButton(sf::Sprite&& sprite, sf::Text&& text, buttonFunc action);

    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTON_HPP__

#ifndef __MENUBUTTON_HPP__
#define __MENUBUTTON_HPP__

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

// using ButtonFunc = void (*)(gameDataRef gameData);
// using ButtonData = struct {const char* title; ButtonFunc action;};

typedef void (*ButtonFunc)(gameDataRef gameData);
typedef struct {const char* title; ButtonFunc action;} ButtonData;

class MenuButton: public Button {
private:
    ButtonFunc action;
public:
    MenuButton(const sf::Sprite& sprite, const sf::Text& text, ButtonFunc action);
    MenuButton(sf::Sprite&& sprite, sf::Text&& text, ButtonFunc action);

    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTON_HPP__

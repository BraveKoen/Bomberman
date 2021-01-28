#ifndef __MENUBUTTONEXT_HPP__
#define __MENUBUTTONEXT_HPP__

#include <functional>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

using buttonFuncExt = const std::function<void(gameDataRef gameData)>;
using buttonDataExt = struct {const char* title; buttonFuncExt action;};

class MenuButtonExt: public Button {
private:
    buttonFuncExt action;
public:
    MenuButtonExt(const sf::Sprite& sprite, const sf::Text& text, buttonFuncExt action);
    MenuButtonExt(sf::Sprite&& sprite, sf::Text&& text, buttonFuncExt action);

    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTONEXT_HPP__

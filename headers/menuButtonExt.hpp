#ifndef __MENUBUTTONEXT_HPP__
#define __MENUBUTTONEXT_HPP__

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "definitions.hpp"
#include <functional>

using buttonDataExt = struct {const char* title; std::function<void()> action;};

class MenuButtonExt: public Button {
private:
    std::function<void()> action;
public:
    MenuButtonExt(
        const sf::Sprite& sprite,
        const sf::Text& text,
        std::function<void()> action
    );
    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTONEXT_HPP__

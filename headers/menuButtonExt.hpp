#ifndef __MENUBUTTONEXT_HPP__
#define __MENUBUTTONEXT_HPP__

#include <functional>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

// using ButtonFuncExt = const std::function<void()>;
// using ButtonDataExt = struct {const char* title; ButtonFuncExt action;};

typedef const std::function<void()> ButtonFuncExt;
typedef struct {const char* title; ButtonFuncExt action;} ButtonDataExt;

class MenuButtonExt: public Button {
private:
    ButtonFuncExt action;
public:
    MenuButtonExt(const sf::Sprite& sprite, const sf::Text& text, ButtonFuncExt action);
    MenuButtonExt(sf::Sprite&& sprite, sf::Text&& text, ButtonFuncExt action);

    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTONEXT_HPP__

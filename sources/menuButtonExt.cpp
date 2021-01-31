#include "../headers/menuButtonExt.hpp"
#include "../headers/button.hpp"
#include "../headers/game.hpp"

MenuButtonExt::MenuButtonExt(
    const sf::Sprite& sprite,
    const sf::Text& text,
    ButtonFuncExt action
):
    Button{sprite, text},
    action{action}
{}

MenuButtonExt::MenuButtonExt(
    sf::Sprite&& sprite,
    sf::Text&& text,
    ButtonFuncExt action
):
    Button{std::move(sprite), std::move(text)},
    action{action}
{}

void MenuButtonExt::invokeAction(gameDataRef) const {
    action();
}

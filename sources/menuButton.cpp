#include "../headers/menuButton.hpp"
#include "../headers/button.hpp"
#include "../headers/game.hpp"

MenuButton::MenuButton(
    const sf::Sprite& sprite,
    const sf::Text& text,
    buttonFunc action
):
    Button{std::move(sprite), std::move(text)},
    action{action}
{}

void MenuButton::invokeAction(gameDataRef gameData) const {
    action(gameData);
}

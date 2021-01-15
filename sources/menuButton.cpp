#include "../headers/menuButton.hpp"

MenuButton::MenuButton(
    const sf::Sprite& sprite,
    const sf::Text& text,
    buttonFunc action
):
    Button{sprite, text},
    action{action}
{}

void MenuButton::invokeAction(gameDataRef gameData) const {
    action(gameData);
}

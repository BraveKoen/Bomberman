#ifndef __MENUBUTTON_HPP__
#define __MENUBUTTON_HPP__

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

using buttonFunc = void (*)(gameDataRef gameData);
using buttonData = struct {const char* title; buttonFunc action;};

/// \brief
/// Derived MenuButton class
/// \details
/// The MenuButtonExt class is derived from the Button class and provides the
/// implementation for the action that needs to take place when an interaction
/// from the user occurs.
class MenuButton: public Button {
private:
    buttonFunc action;
public:
    /// \brief
    /// Constructor for lvalue sprites and texts
    /// \details
    /// Receives a sprite object used for drawing and interaction and a text
    /// object to display a text message on the button. These objects will be
    /// passed a long to the Button constructor. Also receives a pointer to a
    /// function returning void that receives a GameData object. This function
    /// pointer is called whenever the invokeAction() function is executed.
    MenuButton(const sf::Sprite& sprite, const sf::Text& text, buttonFunc action);
    /// \brief
    /// Constructor for rvalue sprites and texts
    /// \details
    /// Receives a sprite object used for drawing and interaction and a text
    /// object to display a text message on the button. These objects will be
    /// moved to the Button constructor. Also receives a pointer to a
    /// function returning void that receives a GameData object. This function
    /// pointer is called whenever the invokeAction() function is executed.
    MenuButton(sf::Sprite&& sprite, sf::Text&& text, buttonFunc action);

    /// \brief
    /// Invokes an action
    /// \details
    /// Provides the implementation whenever an interaction needs to take
    /// place. Passes the received GameData object to the stored action.
    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTON_HPP__

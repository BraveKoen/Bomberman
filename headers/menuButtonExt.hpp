#ifndef __MENUBUTTONEXT_HPP__
#define __MENUBUTTONEXT_HPP__

#include <functional>
#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "definitions.hpp"

using buttonFuncExt = const std::function<void()>;
using buttonDataExt = struct {const char* title; buttonFuncExt action;};

/// \brief
/// Derived MenuButton class
/// \details
/// The MenuButtonExt class is derived from the Button class and provides the
/// implementation for the action that needs to take place when an interaction
/// from the user occurs. This class uses the std::functional library to
/// support the use of fully fledged lambdas with capture functionality.
class MenuButtonExt: public Button {
private:
    buttonFuncExt action;
public:
    /// \brief
    /// Constructor for lvalue sprites and texts
    /// \details
    /// Receives a sprite object used for drawing and interaction and a text
    /// object to display a text message on the button. These objects will be
    /// passed a long to the Button constructor. Also receives a std::function
    /// object of type void(). This function object is called whenever the
    /// invokeAction() function is executed.
    MenuButtonExt(const sf::Sprite& sprite, const sf::Text& text, buttonFuncExt action);
    MenuButtonExt(sf::Sprite&& sprite, sf::Text&& text, buttonFuncExt action);

    /// \brief
    /// Invokes an action
    /// \details
    /// Provides the implementation whenever an interaction needs to take
    /// place. The received GameData object is not passed to the action object.
    virtual void invokeAction(gameDataRef gameData) const override;
};

#endif // __MAINMENUBUTTONEXT_HPP__

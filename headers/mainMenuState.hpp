#ifndef __MAINMENUSTATE_HPP__
#define __MAINMENUSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "definitions.hpp"
#include "menuButton.hpp"

/// \brief
/// main menu state class
/// \details
/// This class is the first screen you see when starting up the game.
/// Will show the player a logo, a play button and an exit button.
class MainMenuState: public State {
private:
    gameDataRef gameData;
    std::vector<MenuButton> menuButtons;
    sf::Sprite background;
    sf::Sprite title;
public:
    /// \brief
    /// MainMenuState constructor
    /// \details
    /// This constructor needs a gameDataRef to work.
    /// It is also pretty mutch all it does.
    MainMenuState(gameDataRef gameData);

    /// \brief
    /// Init function, used to create all objects.
    /// \details
    /// This function will put in a background, the buttons and the title.
    /// It scales all these based on the window size, 
    /// so with a different window size you would still have them in a good position.
    virtual void init() override;

    /// \brief
    /// Handle input function will allow players to use the buttons.
    /// \details
    /// This function will handle the user input.
    /// If a user closes the program by clicking the X, clicking the exit button or pressing the Esc button it will close the program.
    /// If the play button is clicked it will go to the ModeSelectState and put this one on top of the stack (not replacing).
    virtual void handleInput() override;

    /// \brief
    /// Update function
    /// \details
    /// This function currently does not do nor need to do anything.
    /// It is however here for potential future use.
    /// Could be used to poll a server, to do animations or even for a simple timer/clock feature.
    virtual void update(float delta) override;

    /// \brief
    /// Draws all made objects on the screen
    /// \details
    /// This function will draw all objects made in init onto the window declared in the gameData.
    virtual void draw(float delta) override;

    /// \brief
    /// Resume is called if the state comes back into action.
    /// \details
    /// Resumes this state if another state is poped from the stack leaving only this state.
    /// It will switch off any potential multiplayer setting that may have been set.
    /// This means you dont have to restart the game if you want to play multiple multiplayer games.
    virtual void resume() override;
};

#endif // __MAINMENUSTATE_HPP__

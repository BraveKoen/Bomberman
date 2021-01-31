#ifndef __POSTGAMESTATE_HPP__
#define __POSTGAMESTATE_HPP__

#include <array>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "state.hpp"
#include "definitions.hpp"
#include "menuButton.hpp"

/// \brief
/// State for showing the winner after a game
/// \details
/// This state is entered whenever a game finishes, it displays a message showing who won the game with some text and their player profile.
/// The class is derived from the base State class.
class PostGameState : public State {
private:
    gameDataRef gameData;
    uint_fast8_t winnerId;
    sf::Sprite playerProfile;
    sf::Sprite background;
    sf::Text title;
    sf::Text winningText;
    std::vector<MenuButton> menuButtons;

    /// \brief
    /// Creates buttons from buttondata
    /// \details
    /// This functions creates this state's button based the buttondata it is given, which concists of the text to put on the button and a function that it executes when clicked.
    template<auto N>
    void createMenuButtons(const std::array<buttonData, N>& buttons);

    /// \brief
    /// Draws all menu buttons
    /// \details
    /// This function draws all the buttons in the state.
    void drawMenuButtons() const;

    /// \brief
    /// Checks if button get clicked
    /// \details
    /// This function checks for user input, namely wether the user clicks on any of the buttons with LMB.
    void handleButtonInput() const;
public:
    /// \brief
    /// Basic constructor for PostGameState
    /// \details
    /// This constructor calls the constructor with winnerId using default id 0.
    PostGameState(gameDataRef gameData);

    /// \brief
    /// Medium constructor for PostGameState
    /// \details
    /// This constructor calls the constructor with winnerId and playerProfile (sprite) using "gameData->assetManager.loadTexture(Resource::HUD::profiles[winnerId])" to get the correct sprite.
    PostGameState(gameDataRef gameData, uint_fast8_t winnerId);

    /// \brief
    /// Full constructor for PostGameState
    /// \details
    /// This constructor has all required parameters and directly constructs the object.
    PostGameState(gameDataRef gameData, uint_fast8_t winnerId, const sf::Sprite& playerProfile);

    /// \brief
    /// Init function for PostGameState, overrides State::init
    /// \details
    /// This function initiates most of the screen objects this state has, this function is called first by the StateMachine, after it come the handleInput, update and draw functions.
    virtual void init() override;

    /// \brief
    /// handleInput function for PostGameState, overrides State::handleInput
    /// \details
    /// This function handles the user input for the entire state, such as the clicking on buttons, or the closing of the window.
    virtual void handleInput() override;

    /// \brief
    /// update function for PostGameState, overrides State::update
    /// \details
    /// This function updates everything that isnt user input for the state, in this state this boils down to mostly online multiplayer related stuff.
    virtual void update(float delta) override;

    /// \brief
    /// draw function for PostGameState, overrides State::draw
    /// \details
    /// This function draws all screen objects for the class.
    virtual void draw(float delta) override;
};

#endif // __POSTGAMESTATE_HPP__

#ifndef __MODESELECTSTATE_HPP__
#define __MODESELECTSTATE_HPP__

#include <vector>
#include <array>
#include <string>
#include <thread>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "state.hpp"
#include "utilities.hpp"
#include "definitions.hpp"
#include "menuButtonExt.hpp"
#include "mapSelectorState.hpp"
#include "tileMap.hpp"

/// \brief
/// State for selecting game mode
/// \details
/// In this state the user can choose for local or online multiplayer, if local also the number of players.
/// Some server connection stuff is also done here, it acts as a sort of lobby for online.
class ModeSelectState: public State {
private:
    gameDataRef gameData;
    bool showPlayerNumberButtons;
    bool showOnlineNumberButtons;
    std::vector<MenuButtonExt> menuButtons;
    std::vector<MenuButtonExt> playerNumberButtons;
    std::vector<MenuButtonExt> readyButton;
    sf::Sprite background;
    std::map<std::string, bool> stateData;
    std::thread mThread;
    bool startMul = false;
    bool startMapSelect = false;
    bool oneTimePress = true;
public:
    /// \brief
    /// Constructor for ModeSelectState
    /// \details
    /// Only takes a gameDataRef, this constructor doesnt really do much besided the initialization of a couple variables.
    ModeSelectState(gameDataRef gameData);

    /// \brief
    /// Init function for ModeSelectState, overrides State::init
    /// \details
    /// This function initiates most of the screen objects this state has, this function is called first by the StateMachine, after it come the handleInput, update and draw functions.
    virtual void init() override;

    /// \brief
    /// handleInput function for ModeSelectState, overrides State::handleInput
    /// \details
    /// This function handles the user input for the entire state, such as the clicking on buttons, or the closing of the window.
    virtual void handleInput() override;

    /// \brief
    /// update function for ModeSelectState, overrides State::update
    /// \details
    /// This function updates everything that isnt user input for the state, in this state this boils down to mostly online multiplayer related stuff.
    virtual void update(float delta) override;

    /// \brief
    /// draw function for ModeSelectState, overrides State::draw
    /// \details
    /// This function draws all screen objects for the class, in some cases dependant on state variables, i.e. showing the player number buttons after the 'local' button has been pressed.
    virtual void draw(float delta) override;

    /// \brief
    /// Makes buttons from sets of buttondata
    /// \details
    /// This function instantiates most of the button used in this state from a vector of buttonDataExt. It returns a vector of MenuButtonExt that were placed based on the number of buttonDataExt and the offset.
    std::vector<MenuButtonExt> makeButtons(std::vector<buttonDataExt> buttonData, sf::Vector2f offset={0,0});

    /// \brief
    /// Handles server connection for online
    /// \details
    /// This function is usually only called in a seperate thread and is used for lobby related commucation between the client and server.
    void lobbyQueue();
};

#endif // __MODESELECTSTATE_HPP__
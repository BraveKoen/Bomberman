#ifndef __STATEMACHINE_HPP__
#define __STATEMACHINE_HPP__

#include <memory>
#include <stack>

#include "state.hpp"

using stateRef = std::unique_ptr<State>;

/// \brief
/// StateMachine class, handles game states
/// \details
/// This class manages the different states of the game, to accomplish this it has a stack of states that can be added to (with or without replacing) and removed from.
/// Whenever a state is added, without replacing the previous, the StateMachine calls the pause function of the current state before doing so.'
/// Whenever a state is removed the resume function of the new current state is called afterwards.
/// The StateMachine has a seperate processStateChanges function that is called by the game loop after finishing everything for the current state, this means that when a state calls for a statechange it's current loop is finished first.
class StateMachine{
private:
    std::stack<stateRef> statesStack;
    stateRef newState;
    bool isRemoving;
    bool isAdding;
    bool isReplacing;
public:
    /// \brief
    /// Function for adding a new state to the stack
    /// \details
    /// This function essentially tells the StateMachine that it wants to add a new state, and which one, but doesnt actually do it yet. 
    /// Instead a boolean is set and the new state is saved for the time being to be processed when the processStateChanges function is next called.
    void addState(stateRef state, bool replacing=true);

    /// \brief
    /// Function for removing the current state from the stack
    /// \details
    /// This function essentially tells the StateMachine that it wants to get rid of the current state, and resume the one under it.
    /// Instead of immediately doing this it sets a boolean to be processed in the next processStateChanges call.
    void removeState();

    /// \brief
    /// Function that processes all new state changes
    /// \details
    /// This function check if the state changing booleans are set and if so handles their requests by adding a new state, with or without replacing, or removing the current state.
    /// This function is also the one that calls the pause and resume functions when appropriate.
    void processStateChanges();

    /// \brief
    /// Getter for the active state
    /// \details
    /// This function returns a reference to the current active state. This is mostly used by the game loop to call the handleInput, update and draw functions of the currently active state.
    stateRef & getActiveState();
};

#endif // __STATEMACHINE_HPP__

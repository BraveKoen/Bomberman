#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <map>

/// \brief
/// Base class for every state in the game
/// \details
/// This base class has a couple of pure virtual functions that need to be implemented by every derived state, and two virtual functions with empty implementations that only need to be overriden where necessary.
/// All of these functions are called by the StateMachine and Game classes, the init function is called when the state is first added, the handleInput, update and draw functions are called every game loop,
/// the pause function is called whenever a new state is added to the stack that doesnt replace the current and the resume function is called when a state is removed from the stack and the one under it needs to be resumed.
class State {
private:
public:
    /// \brief
    /// Pure virtual init function
    /// \details
    /// This function needs to be implemented for every derived state class, it is called whenever the state is first added to the StateMachine's stack and should handle the initialization of the entire state, kind of like a pseudo constructor.
    virtual void init()=0;

    /// \brief
    /// Pure virtual handleInput function
    /// \details
    /// This function needs to be implemented for every derived state class, it should handle all user input for the state.
    virtual void handleInput()=0;

    /// \brief
    /// Pure virtual update function
    /// \details
    /// This function needs to be implemented for every derived state class, it should handle updating screen objects (using the delta for framerate independant stuff) and other non-user-input related stuff. I.e. physics calculations, player movement, etc.
    virtual void update(float delta)=0;

    /// \brief
    /// Pure virtual draw function
    /// \details
    /// This function needs to be implemented for every derived state class, it should draw every screen object (that needs to be drawn ofcourse) to the window.
    virtual void draw(float delta)=0;

    /// \brief
    /// Virtual pause function with empty implementation
    /// \details
    /// This function should be overriden whenever a state needs to cleanly pause things if a different state is added to the stack without replacing the current. Usually goes paired with an implementation for the resume function.
    virtual void pause(){}

    /// \brief
    /// Virtual resume function with empty implementation
    /// \details
    /// This function should be overriden whenever a state needs to cleanly resume things when the state above in the stack gets removed. Usually goes paired with an implementation for the pause function.
    virtual void resume(){}
};

#endif // __STATE_HPP__
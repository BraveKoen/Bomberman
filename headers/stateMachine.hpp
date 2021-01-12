#ifndef __STATEMACHINE_HPP__
#define __STATEMACHINE_HPP__

#include <memory>
#include <stack>

#include "State.hpp"

typedef std::unique_ptr<State> stateRef;

class StateMachine{
    private:
        std::stack<stateRef> statesStack;
        stateRef newState;
        bool isRemoving;
        bool isAdding;
        bool isReplacing;
    public:
        void addState(stateRef state, bool replacing=true);
        void removeState();
        void processStateChanges();

        stateRef & getActiveState();
};

#endif // __STATEMACHINE_HPP__
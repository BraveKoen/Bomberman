#include "../headers/stateMachine.hpp"

void StateMachine::addState(stateRef state, bool replacing){
    isAdding = true;
    isReplacing = replacing;
    newState = std::move(state);
}

void StateMachine::removeState(){
    isRemoving = true;
}

void StateMachine::processStateChanges(){
    if(isRemoving && !statesStack.empty()){
        statesStack.pop();
        if(!statesStack.empty()){
            statesStack.top()->resume();
        }
        isRemoving = false;
    }
    if(isAdding){
        if(!statesStack.empty()){
            if(isReplacing){
                statesStack.pop();
            }else{
                statesStack.top()->pause();
            }
        }
        statesStack.push(std::move(newState));
        statesStack.top()->init();
        isAdding = false;
    }
}

stateRef & StateMachine::getActiveState(){
    return statesStack.top();
}
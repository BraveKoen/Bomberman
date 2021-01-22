#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <map>

class State {
    private:
    public:
        virtual void init()=0;
        virtual void handleInput()=0;
        virtual void update(float delta)=0;
        virtual void draw(float delta)=0;

        virtual void pause(){}
        virtual void resume(){}

        virtual std::map<std::string, bool>& getStateDataRef(){}
};

#endif // __STATE_HPP__
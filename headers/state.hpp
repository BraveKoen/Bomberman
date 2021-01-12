#ifndef __STATE_HPP__
#define __STATE_HPP__

class State {
    private:
    public:
        virtual void init()=0;
        virtual void handleInput()=0;
        virtual void update(float delta)=0;
        virtual void draw(float delta)=0;

        virtual void pause(){}
        virtual void resume(){}
};

#endif // __STATE_HPP__
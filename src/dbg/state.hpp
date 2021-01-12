#pragma once

class State {
public:
    virtual auto init() -> void = 0;
    virtual auto handleInput() -> void = 0;
    virtual auto update(float delta) -> void = 0;
    virtual auto draw(float delta) -> void = 0;
    virtual auto pause() -> void {}   // note: defines impl.
    virtual auto resume() -> void {}  // note: defines impl.
};

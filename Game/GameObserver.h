#pragma once

namespace chess {

class GameState;


class GameObserver {

public:
    virtual void gameStarted(const GameState &state) = 0;
    virtual void gameEnded(const GameState &state) = 0;
    virtual void turnStarted(const GameState &state) = 0;
    virtual void turnEnded(const GameState &state) = 0;

};


}

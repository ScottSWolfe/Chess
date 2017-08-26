#pragma once

#include <string>
#include "ConsoleBoardPresenter.h"
#include "GameObserver.h"

namespace chess {

enum class GameEndType;
class GameState;


class ConsoleUI : public GameObserver {

public:
    void gameStarted(const GameState &state) override;
    void gameEnded(const GameState &state) override;
    void turnStarted(const GameState &state) override;
    void turnEnded(const GameState &state) override;

private:
    ConsoleBoardPresenter presenter;
    std::string getGameEndMessage(GameEndType end_type) const;
    std::string currentTurnToString(const GameState &newState) const;

};



}
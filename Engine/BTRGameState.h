#pragma once

#include <vector>
#include "GameState.h"
#include "PositionRanker.h"

namespace chess {

class Move;


class BTRGameState : public GameState {

public:
    BTRGameState(const BTRGameState &state);
    BTRGameState(const GameState &state);
    int getRelativePieceValue() const;
    void makeMove(const Move &move);
    void undoLastMove();


private:
    PositionRanker ranker;
    std::vector<int> relative_piece_value_stack;

    void updateRelativePieceValueStack(const Move &move);

};


}

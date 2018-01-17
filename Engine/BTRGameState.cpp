#include "BTRGameState.h"
#include "PositionRanker.h"

namespace chess {


BTRGameState::BTRGameState(const GameState &state) 
    : GameState(state)
{
    PositionRanker ranker;
    relative_piece_value = ranker.rankPosition(state);
}

int BTRGameState::getRelativePieceValue() const {
    return relative_piece_value;
}


}

#include "BTRGameState.h"
#include "Piece.h"
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

void BTRGameState::makeMove(const Move &move) {
    updateRelativePieceValue(move);
    GameState::makeMove(move);
}

void BTRGameState::updateRelativePieceValue(const Move &move) {
    PositionRanker ranker;
    relative_piece_value += ranker.getRelativePieceValueChange(*this, move);
}


}

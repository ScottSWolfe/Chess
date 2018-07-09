#include "BTRGameState.h"
#include "Piece.h"
#include "PositionRanker.h"

namespace chess {


BTRGameState::BTRGameState(const BTRGameState &other)
    : GameState(other), relative_piece_value_stack(other.relative_piece_value_stack)
{}

BTRGameState::BTRGameState(const GameState &state) 
    : GameState(state)
{
    relative_piece_value_stack.push_back(ranker.rankPosition(state));
}

int BTRGameState::getRelativePieceValue() const {
    return relative_piece_value_stack.back();
}

void BTRGameState::makeMove(const Move &move) {
    updateRelativePieceValueStack(move);
    GameState::makeMove(move);
}

void BTRGameState::undoLastMove() {
    relative_piece_value_stack.pop_back();
    GameState::undoLastMove();
}

void BTRGameState::updateRelativePieceValueStack(const Move &move) {
    relative_piece_value_stack.push_back(getRelativePieceValue() + ranker.getRelativePieceValueChange(*this, move));
}


}

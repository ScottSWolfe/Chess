#include <limits>
#include "BTREngine.h"
#include "GameState.h"

namespace chess {


std::shared_ptr<PlayerAction> BTREngine::getAction(const GameState &state) const {
    return getBestMove(state);
}

PieceType BTREngine::getPromotionPiece(const GameState &state, const Move &move) const {
    return PieceType::QUEEN;
}

std::shared_ptr<Move> BTREngine::getBestMove(const GameState &state) const {
    int bestScore = std::numeric_limits<int>::min();
    std::shared_ptr<Move> bestMove(nullptr);
    std::vector<Move> moves = state.getAvailableMoves();
    for (Move move : moves) {
        int score = scoreMove(state, move);
        if (bestScore < score) {
            bestScore = score;
            bestMove = std::make_shared<Move>(move);
        }
    }
    return bestMove;
}

int BTREngine::scoreMove(const GameState &state, const Move &move) const {
    GameState new_state = makeMove(state, move);
    int score = ranker.rankPosition(new_state);
    if (state.getCurrentPlayersTurn() == PieceColor::WHITE) {
        return score;
    }
    else {
        return -score;
    }
}

GameState BTREngine::makeMove(const GameState &state, const Move &move) const {
    GameState new_state = state.getCopy();
    new_state.makeMove(move);
    return new_state;
}


}

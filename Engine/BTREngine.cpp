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
    return scoreMove(state, move, 1, 0);
}

int BTREngine::scoreMove(const GameState &state, const Move &move, int max_depth, int depth) const {
    GameState new_state = makeMove(state, move);
    std::vector<Move> opponents_moves = new_state.getAvailableMoves();
    int bestOpponentScore = std::numeric_limits<int>::min();
    for (Move opp_move : opponents_moves) {
        int score = getScore(new_state, opp_move, max_depth, depth);
        if (score > bestOpponentScore) {
            bestOpponentScore = score;
        }
    }
    return -bestOpponentScore;
}

int BTREngine::getScore(const GameState &state, const Move &move, int max_depth, int depth) const {
    if (depth < max_depth) {
        return scoreMove(state, move, max_depth, depth + 1);
    }
    else {
        GameState new_state = makeMove(state, move);
        return ranker.scorePosition(new_state);
    }
}

GameState BTREngine::makeMove(const GameState &state, const Move &move) const {
    GameState new_state = state.getCopy();
    new_state.makeMove(move);
    return new_state;
}


}

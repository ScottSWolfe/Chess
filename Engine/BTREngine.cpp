#include <limits>
#include "BTREngine.h"
#include "BTRGameState.h"
#include "BTRGameState.h"

namespace chess {


std::shared_ptr<PlayerAction> BTREngine::getAction(const GameState &state) const {
    BTRGameState btr_state(state);
    return getBestMoveUsingThreads(btr_state);
}

PieceType BTREngine::getPromotionPiece(const GameState &state, const Move &move) const {
    return PieceType::QUEEN;
}

std::shared_ptr<Move> BTREngine::getBestMove(const BTRGameState &state) const {
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

std::shared_ptr<Move> BTREngine::getBestMoveUsingThreads(const BTRGameState &state) const {
    std::vector<Move> moves = state.getAvailableMoves();
    int num_moves = moves.size();
    std::vector<int> scores(num_moves);
    std::vector<std::thread> threads(num_moves);
    launchThreads(state, moves, threads, scores);
    joinThreads(threads);
    return chooseBestMoveUsingScores(moves, scores);
}

void BTREngine::launchThreads(const BTRGameState &state, const std::vector<Move> &moves, std::vector<std::thread> &threads, std::vector<int> &scores) const {
    int size = moves.size();
    for (int i = 0; i < size; i++) {
        threads[i] = std::thread(&BTREngine::scoreMoveThreadingWrapper, this, state, moves[i], std::ref(scores[i]));
    }
}

void BTREngine::joinThreads(std::vector<std::thread> &threads) const {
    int size = threads.size();
    for (int i = 0; i < size; i++) {
        threads[i].join();
    }
}

std::shared_ptr<Move> BTREngine::chooseBestMoveUsingScores(const std::vector<Move> &moves, const std::vector<int> &scores) const {
    int bestScore = std::numeric_limits<int>::min();
    std::shared_ptr<Move> bestMove(nullptr);
    int size = moves.size();
    for (int i = 0; i < size; i++) {
        if (bestScore < scores[i]) {
            bestScore = scores[i];
            bestMove = std::make_shared<Move>(moves[i]);
        }
    }
    return bestMove;
}

void BTREngine::scoreMoveThreadingWrapper(const BTRGameState &state, const Move &move, int &result) const {
    result = scoreMove(state, move);
}

int BTREngine::scoreMove(const BTRGameState &state, const Move &move) const {
    int current_depth = 1;
    return scoreMove(state, move, MAX_DEPTH, current_depth);
}

int BTREngine::scoreMove(const BTRGameState &state, const Move &move, int max_depth, int depth) const {
    int opponents_best_score = std::numeric_limits<int>::min();
    const_cast<BTRGameState&>(state).makeMove(move);
    if (state.isGameOver() || depth >= max_depth) {
        opponents_best_score = ranker.scorePosition(state);
    }
    else {
        std::vector<Move> opponents_moves = state.getAvailableMoves();
        for (Move opp_move : opponents_moves) {
            int opponents_score = scoreMove(state, opp_move, max_depth, depth + 1);
            if (opponents_score > opponents_best_score) {
                opponents_best_score = opponents_score;
            }
        }
    }
    const_cast<BTRGameState&>(state).undoLastMove();
    return -opponents_best_score;
}


}

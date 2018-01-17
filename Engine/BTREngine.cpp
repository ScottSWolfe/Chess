#include <limits>
#include "BTREngine.h"
#include "GameState.h"
#include "BTRGameState.h"

namespace chess {


std::shared_ptr<PlayerAction> BTREngine::getAction(const GameState &state) const {
    BTRGameState btr_state(state);
    return getBestMoveUsingThreads(btr_state);
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

std::shared_ptr<Move> BTREngine::getBestMoveUsingThreads(const GameState &state) const {
    std::vector<Move> moves = state.getAvailableMoves();
    int num_moves = moves.size();
    std::vector<int> scores(num_moves);
    std::vector<std::thread> threads(num_moves);
    launch_threads(state, moves, threads, scores);
    join_threads(threads);
    return chooseBestMoveUsingScores(moves, scores);
}

void BTREngine::launch_threads(const GameState &state, const std::vector<Move> &moves, std::vector<std::thread> &threads, std::vector<int> &scores) const {
    int size = moves.size();
    for (int i = 0; i < size; i++) {
        threads[i] = std::thread(&BTREngine::scoreMoveThreadingWrapper, this, state, moves[i], std::ref(scores[i]));
    }
}

void BTREngine::join_threads(std::vector<std::thread> &threads) const {
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

void BTREngine::scoreMoveThreadingWrapper(const GameState &state, const Move &move, int &result) const {
    result = scoreMove(state, move);
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
    GameState new_state(state);
    new_state.makeMove(move);
    return new_state;
}


}

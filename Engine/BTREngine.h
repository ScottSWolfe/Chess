#pragma once

#include <memory>
#include <thread>
#include "Engine.h"
#include "Piece.h"
#include "PlayerAction.h"
#include "PositionRanker.h"

namespace chess {


class BTREngine : public Engine {

public:
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const override;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    PositionRanker ranker;

    std::shared_ptr<Move> getBestMove(const BTRGameState &state) const;
    std::shared_ptr<Move> getBestMoveUsingThreads(const BTRGameState &state) const;
    void launch_threads(const BTRGameState &state, const std::vector<Move> &moves, std::vector<std::thread> &threads, std::vector<int> &scores) const;
    void join_threads(std::vector<std::thread> &threads) const;
    std::shared_ptr<Move> chooseBestMoveUsingScores(const std::vector<Move> &moves, const std::vector<int> &scores) const;
    void scoreMoveThreadingWrapper(const BTRGameState &state, const Move &move, int &result) const;
    int scoreMove(const BTRGameState &state, const Move &move) const;
    int scoreMove(const BTRGameState &state, const Move &move, int max_depth, int depth) const;
    int getScore(const BTRGameState &state, const Move &move, int max_depth, int depth) const;
    BTRGameState makeMove(const BTRGameState &state, const Move &move) const;

};


}

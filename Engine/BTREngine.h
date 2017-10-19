#pragma once

#include <memory>
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

    std::shared_ptr<Move> getBestMove(const GameState &state) const;
    int scoreMove(const GameState &state, const Move &move) const;

};


}

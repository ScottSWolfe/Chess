#pragma once

#include <memory>
#include <vector>
#include "RandomEngine.h"
#include "Player.h"

namespace chess {


class RandomPlayer : public Player {

public:
    RandomPlayer(PieceColor color);
    std::shared_ptr<PlayerAction> getAction(const GameState &state) const;
    PieceType getPromotionPiece(const GameState &state, const Move &move) const override;

private:
    RandomEngine engine;

};


}
